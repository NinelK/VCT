// def.h
#ifndef _DEF
#define _DEF

#define NULL 0
#define FALSE 0
#define TRUE 1
typedef int BOOL;
#define SEED 2

#define PI 3.14159265359 

#define rounder(a) (((a) + ((a) < 0 ? 0.5 : -0.5) < (int)(a))? (int)(a): (int)(a) + 1)

#define VOXSIZE .0025 // [mm]
#define SCALE (VOXSIZE/.0025)
#define sizeX 1.00 				// [mm]
#define sizeY 0.50 				// [mm]
#define sizeMarginX 0.100 		// [mm] from one side
#define sizeMarginY 0.100 		// [mm] from one side
#define MARGINX rounder(sizeMarginX/VOXSIZE)
#define MARGINY rounder(sizeMarginY/VOXSIZE)
#define NVX rounder((sizeX+2*sizeMarginX)/VOXSIZE) // x 3 = 1500
#define NVY rounder((sizeY+2*sizeMarginY)/VOXSIZE) //425
#define NV  (NVX*NVY)
#define NNX (NVX+1)
#define NNY (NVY+1)
#define NN  (NNX*NNY)
#define NRINC 901

#define MAXNRITER 1000
#define ACCURACY .00001


#define IMMOTILITY_CH 1.0*SCALE*SCALE//50
#define JB	5.0
#define JH	4.0
#define G_NCH 100.0

// cells
#define IMMOTILITY 1.2*SCALE*SCALE//50
//#define OVERCROWD 2.0
#define NCX 16
#define NCY 20

//field
#define distanceF 0.005
#define fiberD	0.0025
#define F_DISTANCE rounder(distanceF/VOXSIZE)
#define F_ANGLE 0

#define GN_CM (1000.0/SCALE)
#define GN_FB (20.0/SCALE)
#define gS	0.0			// [1/mm]
#define INHIBITION 10
#define PART 0.5

#define TARGETVOLUME_CM  (0.100*0.020/VOXSIZE/VOXSIZE) // targetvolume [pixels]
#define TARGETVOLUME_FB  (0.080*0.010/VOXSIZE/VOXSIZE) // targetvolume [pixels]
#define STARTVOLUME (TARGETVOLUME_FB/10)
#define INELASTICITY_CM 50.0*SCALE*SCALE*SCALE*SCALE // [-] 1.0E20 // [/mm4] //500
#define INELASTICITY_FB 25.0*SCALE*SCALE*SCALE*SCALE // [-] 1.0E20 // [/mm4] //500
#define NUCLEI_R .010/VOXSIZE
#define NUCL 2.0

#define NOSTICKJ 350.0 //10000// [/mm] contact penalty for none-adhesive surface
#define JCMMD (NOSTICKJ*VOXSIZE)  		// CM-medium
#define JCMCM (0.5*JCMMD) 				// CM-CM
#define JMDMD (0.01*JCMMD) 				// medium-medium
#define JFBMD (0.8*NOSTICKJ*VOXSIZE)	// FB-medium
#define JFBFB (0.5*JFBMD)		 		// FB-FB
#define JFBCM (0.8*JCMMD) 				// FB-CM


#define SQ05 .707107 //sqrt(.5), used often enough to make this convenient

#define MAX_FOCALS_CM 20
#define MAX_FOCALS_FB 50
#define MAX_FOCALS (MAX_FOCALS_CM<MAX_FOCALS_FB ? MAX_FOCALS_FB : MAX_FOCALS_CM)

#endif
