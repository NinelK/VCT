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
	rm ./imgs/*.png

example1:
	cp conf/defs/def1.h def.h
	cp conf/various/cnfgSNa.cfg conf/cnfgSN.cfg
	cp conf/various/cnfgSFa.cfg conf/cnfgSF.cfg
	cp conf/various/cnfgMNa.cfg conf/cnfgMN.cfg
	cp conf/various/cnfgMFa.cfg conf/cnfgMF.cfg
	mkdir -p imgs
	rm *.o

example2:
	cp conf/defs/def2.h def.h
	cp conf/various/cnfgSF2.cfg conf/cnfgSF.cfg
	mkdir -p imgs
	rm *.o

example3:
	cp conf/defs/def3.h def.h
	cp conf/various/cnfgMN3.cfg conf/cnfgMN.cfg
	mkdir -p imgs
	rm *.o

example3L:
	cp conf/defs/def3L.h def.h
	cp conf/various/cnfgMN3.cfg conf/cnfgMN.cfg
	mkdir -p imgs
	rm *.o

example4:
	cp conf/defs/def4.h def.h
	cp conf/various/cnfgMN3.cfg conf/cnfgMN.cfg
	mkdir -p imgs
	rm *.o

.c.o:
	cc $(CFLAGS) -O -c $< -o $@
