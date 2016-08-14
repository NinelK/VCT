import os
import random

os.system("rm output.txt");

for i in range(10):

        #values = [(v+2*d*(random.random()-0.5)) for v, d in zip(val,diap)]
        #values = val

        #values_str = ",".join(["%0.2f" % v for v in values ])

        params = "%d,%d" % (
                random.randint(1,100),
                2001
                #values_str
                #2.0,
                #100*(i+1)
        )

        #print params
        print i

        os.system("./cpmfem -s -f -m -p "+params);
        os.system("echo \"{"+params+"}\" >> params.txt");
        os.system("/Applications/Mathematica.app/Contents/MacOS/MathKernel -noprompt -run \"<<params.m\"");
        #os.system("math -noprompt -run \"<<params.m\"");
