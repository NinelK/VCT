import os
import random

os.system("rm output.txt");

#val = [86.9, 1.0, 82.36, 769.36, 32.88, 239.61, 19.34] # CM 1510.61, 0.744243, 3.67651, 6.
#val = [108.45, 0.95, 82.73, 789.75, 34.35, 273.45, 22.41] # CM 1341.66, 0.728573, 3.76872, 5.20408
#val=[75.25, 0.95, 87.07, 773.31, 32.07, 260.26, 4.67] # FB 1361.5, 0.616325, 2.68204, 5.63265
#val = [4.68, 0.9, 95.47, 844.41, 33.84, 139.49, 5.62] # FB 1206.25, 0.668636, 2.76109, 6.63265
#diap =[25.9998, 0.11296, 10.8592, 25.0043, 4.47345, 44.2883, 2.17884] # for FB
#diap = [3.1, 0.11, 20.0, 138.0, 19.6, 25.7, 5.0]

val = [ 108.45, 0.95, 82.73, 789.75,            #CM: GN, Vt, lamb, NOST
        4.68, 0.9, 95.47, 844.41,               #FB: GN, Vt, lamb, NOST
        34.0, 273.45, 139.49,                   # JMM, JCMMD, JFBMD
        22.41, 5.62]                            # INHIB

diap = [25.0, 0.11, 20.0, 150.0,                #CM: GN, Vt, lamb, NOST
        3.0 , 0.11, 20.0, 150.0,                #FB: GN, Vt, lamb, NOST
        20.0, 40.0, 25.0,                       # JMM, JCMMD, JFBMD
        10.0, 5.0]                              # INHIB

#values = val[:];
#params="{:0.2f}".format(values[0])+","+"{:0.2f}".format(values[1])+","+"{:0.2f}".format(values[2])+","+"{:0.2f}".format(values[3])+","+"{:0.2f}".format(values[4])+","+"{:0.3f}".format(values[5])+","+"{:0.2f}".format(values[6]);
#os.system("./cpmfem -s -p "+params);
#os.system("echo \"{"+params+"}\" >> params.txt");
#os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");

for i in range(500):

        values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
        #values = val

        values_str = ",".join(["%0.2f" % v for v in values ])

        params = "%d,%s" % (
                #random.randint(1,100),
                2.0,
                values_str
        )

        #print params
        print i

        os.system("./cpmfem -s -f -p "+params);
        os.system("echo \"{"+params+"}\" >> params.txt");
        os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
        #os.system("math -noprompt -run \"<<params.m\"");
