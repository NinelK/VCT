
import os
import random

os.system("rm output.txt");

val=[75.0, 2.0, 200, 950.0, 400.0]
#val=[70.15, 2.14, 240.67, 909.14, 436.79]			#CMs SNO
#val=[94.74, 2.34, 173.95, 1026.17, 545.27]			#CMs SNO
#val=[54.56, 1.94, 235.71, 944.92, 274.61]			#FBs SNO
diap=[50.0, 1.0, 100.0, 100.0, 250.0];

for i in range(1000):

	values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	#values = val

	values_str = ",".join(["%0.2f" % v for v in values ])

	params = "%d,%d,%s" % (
		2,
		901,
		values_str
	)

	#print params

	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	os.system("math -noprompt -run \"<<params.m\"");

