import os
import numpy as np

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import axes3d
from scipy.optimize import curve_fit

files = os.listdir(".")

def sigm(x, a, b):
	return 1 / (1 + np.exp((x-a)/b))

def parse(strs):
	P = strs[1].split(".txt")
	Ebond = float(strs[0][1:])
	PRC = float(P[0][1:])
	return Ebond, PRC

def frange(x, y, jump):
  while x <= y:
    yield x
    x += jump

def count_connections(strs):
	c = 0.0
	for s in strs:
		#print(s,c)
		if s=='3':
			c+= 1.0
		elif s=='2' or s=='1':
			c+= 0.5
		else:
			c+= 0.0
	return c/float(len(strs))

data = []
for file in files: 
	if file.endswith(".txt"):
		with open(file,"r") as f:
			s = f.readlines()
			Ebond, PRC = parse(file.split("_")[2:])
			cc = count_connections(s[1].split(" ")[:-1])
			data.append([Ebond, PRC, cc])
			#print s[1].split(" ")[:-1],PRC,cc
			#print("%.1f %.2f -- %.2f" % (Ebond, PRC, cc))

nd = np.array(data)

# Two subplots, unpack the axes array immediately
# f, subplots = plt.subplots(2, sharex=True)

# for E,sp in zip([0.0,2.0],subplots):
# 	d = np.sort(nd[nd[:,0] == E],axis = 0)
# 	sp.plot(d[:,1], d[:,2])
# 	sp.set_title('E_bond = %.1f' % E)

fig, (ax1, ax2) = plt.subplots(2,figsize=(6,9))

Ebonds = np.array([0.0,2.5,5.0,7.5,10.0])
fs = np.zeros_like(Ebonds)

print("50%:")
for k,E in enumerate(Ebonds): #[0.0,2.0,4.0,5.0,6.0,8.0]:
 	a = nd[nd[:,0] == E]
 	a = np.array(sorted(a, key=lambda a_entry: a_entry[1]) )
 	ax1.scatter(a[:,1], a[:,2], label="E_bond = %.1f" % E)
 	popt, pcov = curve_fit(sigm, a[:,1], a[:,2])
 	xdata = np.linspace(0.59, 0.78, 50)
 	ax1.plot(xdata, sigm(xdata, *popt))
 	#for f,p in zip(a[:,1],a[:,2]):
 	for i in range(len(a[:,1])):
 		if a[i,2]<0.5:
 			fs[k] = a[i-1,1] + (a[i,1] - a[i-1,1])*(0.5 - a[i-1,2])/(a[i,2] - a[i-1,2]) 
 			f = popt[0] + popt[1] * np.log(1/0.5 - 1)
 			print("E_bond %.1f: %.3f - %.3f" % (E,fs[k],f))
  			break

print fs

ax2.plot(np.array(Ebonds),np.array(fs),label = "Probability 50%")

print("10%:")
for k,E in enumerate(Ebonds): #[0.0,2.0,4.0,5.0,6.0,8.0]:
 	a = nd[nd[:,0] == E]
 	a = np.array(sorted(a, key=lambda a_entry: a_entry[1]) )
 	for i in range(len(a[:,1])):
 		if a[i,2]<0.1:
 			fs[k] = a[i-1,1] + (a[i,1] - a[i-1,1])*(0.1 - a[i-1,2])/(a[i,2] - a[i-1,2]) 
 			print("E_bond %.1f: %.3f" % (E,fs[k]))
 			break

ax2.plot(np.array(Ebonds),np.array(fs),label = "Probability 10%")

ax1.axhline(y=0.5,linestyle="--",color = "black")
ax1.text(0.59, 0.53, "50%", fontsize=12)
ax1.axhline(y=0.1,linestyle="--",color = "black")
ax1.text(0.59, 0.13, "10%", fontsize=12)
ax2.axvline(x=5.0,linestyle="--",color = "r")

ax1.legend()
ax2.legend()
 	
#3D plot

# xi = npdata[:,0]
# yi = npdata[:,1]
# zi = npdata[:,2]
# fig = plt.figure(figsize=(8,6))

# ax = fig.add_subplot(1, 1, 1, projection='3d')

# ax.scatter(yi, xi, zi)
fig.savefig("fig.pdf")
