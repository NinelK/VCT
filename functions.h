// file: functions.h
#include "def.h"
#include "structures.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// init.c
int* 		alloc_attach(int NRc);
VOX*		init_voxels(void);
int 		init_cells(VOX* pv, int * types, BOX* pb);
FIBERS* 	set_fibers(void);


// cellmoves.c
double 		CPM_moves(VOX* pv, short * CCAlabels,BOX* pb, FIBERS* pf, 
CM* CMs, int* attached, int* csize);
double 		CH_moves(VOX* pv, CM* CMs, double k);
BOOL 		splitcheckCCR(VOX* pv, short * CCAlabels, BOX* pb,  
int* csize, int xt, int ttag);

// CM.c
CM* 		allocCM(int NRc);
BOX*		allocBOX(int NRc);
void 		findCM(VOX* pv, CM* CMs, int NRc);

// CPM_dH.c
// distribute channels
double 		calcdH_CH(VOX* pv, CM* CMs, int xt, int xs);
double 		calcdHborder(VOX* pv, int xt, int ttag);
double 		calcdHdist(VOX* pv, CM* CMs, int xt, int xs, int ttag);

//calculate H
double 		calcdH(VOX* pv, FIBERS* pf, CM* CMs, int* csize, int xt, int xs, int pick, int ttag, int stag);
double 		calcdHcontact(VOX* pv, int xt, int xs, int ttag, int stag);
double 		contactenergy(int tag1, int tag2, int type1, int type2);
double 		scaffoldenergy(int tag, int Q);
double 		calcdHvol(int* csize, int ttag, int stag, int ttype, int stype);
double 		calcdHprotrude(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag, int Qt, int Qs);
double 		calcdHsyncytium(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag);
double 		calcdHnuclei(VOX* pv, CM* CMs, int xt, int ttag, int stag);

double 		findphi(CM* CMs, int xt, int tag);
double 		dist(CM* CMs, int xt, int tag);

double		sqr(double x);

// write.c
void   		write_increment(int increment);
void 		write_cells(VOX* pv, int increment);
void 		write_types(int* types, int NRc);
void 		write_contacts(VOX* pv, int increment);
void 		write_fibers(FIBERS* pf);
void 		read_cells(VOX* pv, int* types, int NRc, char filename_ctag[40], char filename_cont[40], char filename_types[40]);

// mylib.c
void 		myitostr(int n, char s[]);
void 		myreverse(char s[]);
unsigned 	mystrlen(const char *s);

// mt.c
void 		mt_init();
unsigned long mt_random();


