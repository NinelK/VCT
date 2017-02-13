import os
import random

#os.system("rm output.txt");

for i in range(1):

	print i

	params = "%d,%d" % (2,10001);

	# #values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	# values = val
	
	# if (2*values[9]<values[11]) or (2*values[10]<values[12]) or (values[9]+values[10]<values[13]) :
		
	# 	print "Bad Js"
	
	# else:

	# 	values_str = ",".join(["%0.2f" % v for v in values ])

	# 	params = "%d,%d,%s" % (
	# 		#random.randint(1,100),
	# 		2,
	# 		2001,
	# 		values_str
	# 	)

		#print params

	os.system("./cpmfem -m -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	os.system("math -noprompt -run \"<<params.m\"");
