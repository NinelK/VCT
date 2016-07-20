import os
import random

os.system("rm output.txt");

val=[1., 4.38, 1.37, 98.75, 943.6, 30.961, 201.75]
#val = [1., 17.87, 1.08, 97.4, 2362.3, 57.66, 466.0]
#values0=[1., 68.8, 1.6, 189., 1521., 36., 545.];
diap=[0.5, 5.0, 0.5, 50.0, 1300.0, 20.0, 200.0];

values = val[:];
params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
os.system("./cpmfem -s -p "+params);
os.system("echo \"{"+params+"}\" >> params.txt");
os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

for i in range(100):

	values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	
	params="{:0.2f}".format(val[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
	
	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
