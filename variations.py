
import os
import random

os.system("rm output.txt");

#val=[446.27, 0.56, 52.49, 105.48, 269.33, 0.56, 41.72, 508.99, 1477.34, 478.56, 563.46, 588.63, 834.22, 91.83, 140.36, 44.9, 35.66]
val=[116.54, 1.41, 53.96, 348.38, 26.87, 1.03, 100.58, 548.57, 394.89, 376.33, 1556.42, 814.04, 1219.6, 56.53, 27.23]
#diap=[63.406, 0.413, 70.966, 581.287, 20.881, 0.196, 81.319, 437.003, 672.594, 427.507, 800.917, 400.428, 647.739, 25.221, 32.48];
##val=[130.42, 0.55, 261.73, 443.06, 576.36, 0.57, 60.83, 270.74, 699.12, 769.4, 825.25, 488.91, 798.11, 54.89, 94.97, 29.42, 27.31]
#diap=[70.0, 0.5, 150.0, 600.0, 20.0, 0.5, 70.0, 500.0, 400.0, 200.0, 600.0, 250.0, 450.0, 30.0, 30.0];
#val=[85.02, 2.11, 226.36, 893.31, 583.95]			#CMs SN 21
#val=[44.27, 1.72, 220.98, 999.72, 319.62]			#FBs SN 24

for i in range(1):

	#values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
	values = val

	values_str = ",".join(["%0.2f" % v for v in values ])

	params = "%d,%d,%s" % (
		#random.randint(1,100),
		2,
		2001,
		values_str
	)

	#print params

	os.system("./cpmfem -m -p "+params);
	os.system("echo \"{"+params+"}\" >> params.txt");
	#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
	os.system("math -noprompt -run \"<<params.m\"");

