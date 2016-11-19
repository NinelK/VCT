
import os
import random

os.system("rm output.txt");

#val=[320.0,  0.58, 270.0, 480.0, 1630.0, 654.0, 51.0, 30.0]
val=[212.57, 0.59, 143.73, 341.07, 221.59, 0.56, 61.62, 282.18, 592.3, 
436.23, 382.34, 489.53, 649.37, 41.77, 84.75, 24.18, 26.59]
#diap=[193.115, 0.03, 184.745, 200.5, 379.245, 0.095, 10.21, 151.845, 334.76, 234.26, 465.245, 162.82, 196.35, 18.365, 50.105, 4.23, 2.85]
#val=[85.02, 2.11, 226.36, 893.31, 583.95]			#CMs SN 21
#val=[44.27, 1.72, 220.98, 999.72, 319.62]			#FBs SN 24

for i in range(1):

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	values = val

	values_str = ",".join(["%0.2f" % v for v in values ])

	params = "%d,%d,%s" % (
		random.randint(1,100),
		3001,
		values_str
	)

	#print params

	os.system("./cpmfem -m -f -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	os.system("math -noprompt -run \"<<params.m\"");

