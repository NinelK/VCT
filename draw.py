import numpy as np
from numpngw import write_png

def make_image(n_int, CMs_ind):

	n = str(n_int)
	
	table=np.loadtxt('./output/ctags'+n+'.out', skiprows=1)
	img = np.ones(table.shape+(3,), dtype=np.uint8)*255
	conts=np.loadtxt('./output/contactM'+n+'.out', skiprows=1)	

	edges = np.zeros(table.shape, dtype = np.uint8)
	vert = table[:,1:] != table[:,:-1]
	hor  = table[1:,:] != table[:-1,:]
	edges[:,1:]   = vert
	edges[:,:-1] += vert
	edges[1:,:]  += hor
	edges[:-1,:] += hor
	edges = np.uint8(edges != 0)

	#CMs = vselect_CMs(table)
	#FBs = vselect_FBs(table)

        is_CM = np.vectorize(lambda x: x in CMs_ind)

        null = np.uint8(table == 0)
        CMs = is_CM(table).astype('uint8')
        FBs = np.ones_like(table) - null - CMs

	#img[:,:,:] = 255
	img[:,:,0] = CMs*(1-0.5*edges)*255 + FBs*(1-0.5*edges)*255
	#+conts*edges*CMs*255+conts*edges*FBs*255
	img[:,:,1] = FBs*(1-0.5*edges)*255
	#+conts*edges*CMs*255
	img[:,:,2] = FBs*(1-0.5*edges)*255

	areas = np.zeros(4)
	conv = (2.5/1000)**2 #to mm
	areas = (np.sum(CMs)*conv,np.sum(FBs)*conv)

	write_png("./imgs/example%05d.png" % n_int, img)

	return areas


types=np.loadtxt('./output/types.out', dtype=np.uint8)
CMs_ind = np.where(types==1)[0]+1
FBs_ind = np.where(types==2)[0]+1

print (len(CMs_ind),len(FBs_ind), 1.0*len(CMs_ind)/(len(CMs_ind)+len(FBs_ind)))

#def select_CMs(a):
#	if (a in CMs_ind):
#		res = 1
#	else:
#	 	res = 0
#	return res	

#def select_FBs(a):
#	if (a in FBs_ind):
#		res = 1
#	else:
#		res = 0
#	return res

#vselect_CMs = np.vectorize(select_CMs)
#vselect_FBs = np.vectorize(select_FBs)

for n in range(0,2001,500):
	print make_image(n, CMs_ind)
