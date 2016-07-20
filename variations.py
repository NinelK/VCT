import os
import random

os.system("rm output.txt");

val=[1., 8.,   1.1, 62.5, 1375., 34.4, 290.]
#values0=[1., 68.8, 1.6, 189., 1521., 36., 545.];
diap=[0.5, 5.0, 0.3, 10.0, 500.0, 5.0, 50.0];

values = val[:];
params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
os.system("./cpmfem -s -p "+params);
os.system("echo \"{"+params+"}\" >> params.txt");
os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

for i in range(100):

	values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	
	params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
	
	os.system("./cpmfem -s -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
