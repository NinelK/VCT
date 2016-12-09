import os
import random

os.system("rm output.txt");

#val=[90.115, 0.95, 250.025, 15.0, 49.91, 0.80, 92.385, 15.0, 559.165, 350.2, 659.72, 251.3, 600.325, 50.555, 54.91]
#diap=[80.1025, 0.20, 241.093, 12.0, 46.26, 0.25, 90.3825, 12.0, 470.0875, 300.0, 426.65, 212.73, 600.007, 27.0425, 26.15]

val=[461.36, 0.6, 26.42, 155.62, 233.76, 0.35, 14.24, 53.21, 937.13, 560.27, 631.42, 267.25, 1152.05, 117.94, 66.93, 62.37, 65.05]
#diap=[20.0, 0.195, 40.705, 20.6, 4.84, 0.14, 10.255, 8.71, 423.565, 242.59, 418.06, 210.515, 546.435, 26.835, 25.355]

#for MF
#val=[461.36, 0.6, 26.42, 155.62, 233.76, 0.35, 14.24, 53.21, 937.13, 560.27, 631.42, 267.25, 1152.05, 117.94, 66.93, 62.37, 65.05]
#diap=[250.0, 0.03, 17.0, 90.0, 202.88, 0.15, 20.00, 90.0, 400.21, 340.14, 447.29, 276.88, 372.07, 67.65, 123.99, 31.53, 30.12]

#val=[9.62, 0.93, 68.05, 15.2, 305.8, 1.44, 48.72]
#diap=[0.955, 0.14, 53.575, 4.555, 31.33, 1.385, 16.26]

for i in range(1):

	print i

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	values = val
	
	if (2*values[9]<values[11]) or (2*values[10]<values[12]) or (values[9]+values[10]<values[13]) :
		
		print "Bad Js"
	
	else:

		values_str = ",".join(["%0.2f" % v for v in values ])

		params = "%d,%d,%s" % (
			#random.randint(1,100),
			2,
			2001,
			values_str
		)

		#print params

		os.system("./cpmfem -m -f -s -p "+params);
		os.system("echo \"{"+params+"}\" >> params.txt");
		#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
		os.system("math -noprompt -run \"<<params.m\"");
