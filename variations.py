import os;

os.system("rm output.txt");

values0=[1.0,20.0,1.2,53.0,1200.0,0.005,0.21];
dvalues=[0.25,2.0,0.1,10.0,25.0,0.001,0.02];
values=[];

i=0;

values = values0[:];
params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
os.system("./cpmfem -s -f -p "+params);
os.system("echo \"{"+params+"}\" >> params.txt");
os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

while i<=0:

	values = values0[:];

	j=-1.0;

	while j<=1.0:

		values[i]=values0[i]+j*dvalues[i];

		params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
	
		os.system("./cpmfem -s -f -p "+params);
		os.system("echo \"{"+params+"}\" >> params.txt");
		os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

		j+=2.0;

	i+=1;
