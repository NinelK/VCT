// def.h
#ifndef _DEF
#define _DEF

#define NULL 0
#define FALSE 0
#define TRUE 1
typedef int BOOL;
#define SEED 2

#define rounder(a) (((a) + ((a) < 0 ? 0.5 : -0.5) < (int)(a))? (int)(a): (int)(a) + 1)

#define VOXSIZE .0025 // [mm]
#define SCALE (VOXSIZE/.0025)
#define sizeX 1.75 				// [mm]
#define sizeY 1.75 				// [mm]
#define sizeMargin 0.125 		// [mm] from one side
#define MARGIN rounder(sizeMargin/VOXSIZE)
#define NVX rounder((sizeX+2*sizeMargin)/VOXSIZE) // x 3 = 1500
#define NVY rounder((sizeY+2*sizeMargin)/VOXSIZE) //425
#define NV  (NVX*NVY)
#define NNX (NVX+1)
#define NNY (NVY+1)
#define NN  (NNX*NNY)
#define NRINC 701

#define MAXNRITER 1000
#define ACCURACY .00001


#define IMMOTILITY_CH 1.0*SCALE*SCALE//50
#define JB	10.0
#define G_NCH 100.0

// cells
#define IMMOTILITY 1.0*SCALE*SCALE//50
//#define OVERCROWD 2.0
#define NCX 28
#define NCY 28

//field
#define FIELD_POWER_MIN 2.0*SCALE
#define FIELD_POWER_MAX 2.0*SCALE
#define FIELD_POWER (FIELD_POWER_MAX - FIELD_POWER_MIN)
#define distanceF 0.05
#define F_DISTANCE rounder(distanceF/VOXSIZE)

#define G_N (2000.0/SCALE)
#define gS	0.0			// [1/mm]


#define CELLDIAM .020 // cell diameter [mm]
#define CELLRVOX (CELLDIAM/2/VOXSIZE) // cell radius [pixels]
#define CELLLENGTH .200 // cell length
#define TARGETVOLUME  (CELLDIAM*CELLLENGTH/VOXSIZE/VOXSIZE) // targetvolume [pixels]
#define STARTVOLUME (TARGETVOLUME/10)
#define INELASTICITY 500.0*SCALE*SCALE*SCALE*SCALE // [-] 1.0E20 // [/mm4] //500
#define NUCLEI_R .020/VOXSIZE

#define Rc 4

//#define NC ((int) sqrt(NVX*NVY/TARGETVOLUME) + 1)			//number of cells in a row/column

#define NOSTICKJ 1200.0 //10000// [/mm] contact penalty for none-adhesive surface
#define JCM (NOSTICKJ*VOXSIZE)  // cell-medium
#define JCC (1.2*JCM) // cell-cell

#define SQ05 .707107 //sqrt(.5), used often enough to make this convenient

#define PI 3.14159265359 

#define MAX_FOCALS 20

#endif
