import os
import random

os.system("rm output.txt");

val=[1., 6.12, 1.29, 100.11, 943.52, 34.209, 217.11]
#val=[1., 73.2, 1.78, 196.06, 1139.55, 46.547, 469.81];
#val = [1., 17.87, 1.08, 97.4, 2362.3, 57.66, 466.0]
#values0=[1., 68.8, 1.6, 189., 1521., 36., 545.];
diap=[0.1, 2.0, 0.1, 10.0, 30.0, 5.0, 30.0];

#values = val[:];
#params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
#os.system("./cpmfem -s -p "+params);
#os.system("echo \"{"+params+"}\" >> params.txt");
#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

for i in range(100):

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	values = val

	params="{:d}".format(random.randint(1,100))+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
	
	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
