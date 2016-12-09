
import os
import random

os.system("rm output.txt");

#val=[45.35, 0.97, 311.08, 8.63, 32.67, 0.81, 48.98, 6.94, 540.68, 240.38, 534.91, 308.83, 444.44, 50., 50.]			//good		900
#val=[73.13, 0.94, 162.94, 8.83, 50.75, 0.93, 140.98, 8.23, 568.02, 296.02, 508.62, 389.23, 516.41, 75.25, 38.28]		//better	900
#val=[274.03, 0.57, 53.09, 15.2, 262.88, 0.51, 45.65, 15.2, 1766.21, 949.14, 547.29, 276.88, 572.07, 87.65, 143.99, 41.53, 40.12]
#diap=[250.0, 0.03, 50.0, 10.2, 202.88, 0.09, 40.65, 10.2, 1266.21, 749.14, 347.29, 176.88, 372.07, 67.65, 73.99, 31.53, 30.12]
#val=[212.11, 1.25, 51.7, 14.115, 446.62, 27.705, 44.83]
#diap=[100.92, 0.15, 49.44, 8.4375, 111.945, 26.5725, 27.19]

for i in range(10):

	print (i+1)

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	#values = val

	#values_str = ",".join(["%0.2f" % v for v in values ])

	params = "%d,%d" % (
		#random.randint(1,100),
		i+1,
		901
		#values_str
	)

	#print params

	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	#os.system("math -noprompt -run \"<<params.m\"");

