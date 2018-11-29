import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

import numpy as np
import os
import sys
import scipy.ndimage as ndimage
from numpngw import write_png
import time

from joblib import Parallel, delayed
import multiprocessing

def make_image(n_int, CMs_ind):

	RIM = 64

	n = str(n_int)
	
	table=np.loadtxt('./output/ctags'+n+'.out', skiprows=1)

	is_CM = np.vectorize(lambda x: x in CMs_ind)

	null = np.uint8(table == 0)
	CMs = is_CM(table).astype('uint8')
	FBs = np.ones_like(table) - null - CMs

	img,labels = ndimage.label(CMs)

	#areas = np.zeros(4)
	#conv = (2.5/1000)**2 #to mm
	#areas = (np.sum(CMs)*conv,np.sum(FBs)*conv)

	intersect_LR = np.intersect1d(np.ndarray.flatten(img[0:RIM,:]),np.ndarray.flatten(img[-RIM:-1,:]))
	intersect_TB = np.intersect1d(np.ndarray.flatten(img[:,0:RIM]),np.ndarray.flatten(img[:,-RIM:-1]))

	res = (len(intersect_TB)>1)*2+(len(intersect_LR)>1)*1

	# 3 -- all
	# 2 -- top-bottom connected only
	# 1 -- left-right connected only
	# 0 -- disconnected

	#print(res)

	#plt.imshow(img)
	#plt.imsave("./imgs/example%05d.png" % n_int,img)

	return res

def compute_sample(SEED):
	os.chdir("sample_S%d_E%.1f_P%.2f" % (SEED, E_bond, PRC))
	time.sleep(2)
	os.system("mkdir output")
	#os.system("mkdir imgs")
	os.system("./cpmfem -c -s -m -p %d,%f,%f,%f" % (SEED,(T+1),E_bond,PRC))

	types=np.loadtxt('./output/types.out', dtype=np.uint8)
	CMs_ind = np.where(types==1)[0]+1
	FBs_ind = np.where(types==2)[0]+1

	PRC_real = 1.0*len(FBs_ind)/(len(CMs_ind)+len(FBs_ind))	#the actaul percentage of FB cells in the sample

	#print("%.2f\n" % PRC_real)

	#print 'N CMs:',len(CMs_ind),'; N FBs:',len(FBs_ind),'; % FBs:', 1.0*len(FBs_ind)/(len(CMs_ind)+len(FBs_ind))

	#make_image(int(sys.argv[1]), CMs_ind)

	# with open("../results/res_S%d_E%.1f_P%.2f.txt" % (SEED,E_bond,PRC),"w") as f:
	# 	f.write("%.4f\n" % PRC_real)
	# 	for n in range(Ts,(T+1),dT):
	# 		res = make_image(n, CMs_ind)
	# 		f.write("%d, %d \n" % (n,res))
	# 	f.close()

	res = make_image(T, CMs_ind)
	# print(os.getcwd())
	# res = 0

	#os.system("mv imgs ../imgs_S%d_E%.1f_P%.2f" % (SEED, E_bond, PRC))

	return res


E_bond = float(sys.argv[1])
PRC = float(sys.argv[2])
seed_start = int(sys.argv[3])
T = 20000
Ts = 20000
dT = 1000

print("Arguments %.1f %.2f" % (E_bond, PRC))

num_cores = multiprocessing.cpu_count()

print(num_cores)

seeds = range(seed_start,seed_start+20,1)

for s in seeds:
	os.system("mkdir sample_S%d_E%.1f_P%.2f" % (s, E_bond, PRC))
	os.system("cp ./cpmfem sample_S%d_E%.1f_P%.2f" % (s, E_bond, PRC))

results = Parallel(n_jobs=num_cores)(delayed(compute_sample)(s) for s in seeds)

print results

with open("./results/result_mid%d_E%.1f_P%.2f.txt" % (seed_start,E_bond,PRC),"w") as f:
		f.write("T: %d\n" % T)
		for r in results:
			f.write("%d " % r);
		f.close()


#print(os.getcwd())

for s in seeds:
	os.system("rm -r sample_S%d_E%.1f_P%.2f" % (s, E_bond, PRC))


