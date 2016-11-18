
import os
import random

os.system("rm output.txt");

#val=[70.006, 2.016, 174.24, 938.89, 543.284]
val=[85.02, 2.11, 226.36, 893.31, 583.95]			#CMs SN 21
#val=[44.27, 1.72, 220.98, 999.72, 319.62]			#FBs SN 24
#diap=[36.7767, 0.31356, 146.839, 153.951, 131.606];

for i in range(10):

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	values = val

	values_str = ",".join(["%0.2f" % v for v in values ])

	params = "%d,%d,%s" % (
		random.randint(1,100),
		901,
		values_str
	)

	#print params

	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	os.system("math -noprompt -run \"<<params.m\"");

