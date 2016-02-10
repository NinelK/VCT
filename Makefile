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
	cc $(LDFLAGS) -O -o cpmfem $(OBJECTS)	

clean:
	rm *.o
	rm ./output/*.out

.c.o:
	cc $(CFLAGS) -O -c $< -o $@
