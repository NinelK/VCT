OBJECTS = CPM_dH.o \
	cellmoves.o \
	CM.o \
	init.o \
	mt.o \
	mylib.o \
	cpmfem.o \
	write.o

# include standard C library
LDFLAGS += -lc 
# include standard math library
LDFLAGS += -lm

CFLAGS += -std=c99

cpmfem: $(OBJECTS)
	mkdir -p output
	cc -O -o cpmfem $(OBJECTS) $(LDFLAGS)

clean:
	rm *.o
	rm ./output/*.out

example1:
	cp conf/defs/defS.h def.h
	cp conf/various/cnfgSNa.cfg conf/cnfgSN.cfg
	cp conf/various/cnfgSFa.cfg conf/cnfgSF.cfg
	rm *.o

example2:
	cp conf/defs/defM.h def.h
	cp conf/various/cnfgMNa.cfg conf/cnfgMN.cfg
	cp conf/various/cnfgMFa.cfg conf/cnfgMF.cfg
	rm *.o

.c.o:
	cc $(CFLAGS) -O -c $< -o $@
