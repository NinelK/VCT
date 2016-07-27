// def.h
#ifndef _DEF
#define _DEF

#define NULL 0
#define FALSE 0
#define TRUE 1
typedef int BOOL;
//#define SEED 2
int SEED;

#define PI 3.14159265359 

#define rounder(a) (((a) + ((a) < 0 ? 0.5 : -0.5) < (int)(a))? (int)(a): (int)(a) + 1)

//sample size
#define VOXSIZE .0025 			// [mm]
#define SCALE (VOXSIZE/.0025)	//
#define sizeX 1.0 				// [mm]
#define sizeY 1.0 				// [mm]
#define sizeMarginX 0.100 		// [mm] from one side
#define sizeMarginY 0.100 		// [mm] from one side
#define MARGINX rounder(sizeMarginX/VOXSIZE)
#define MARGINY rounder(sizeMarginY/VOXSIZE)
#define NVX rounder((sizeX+2*sizeMarginX)/VOXSIZE) 
#define NVY rounder((sizeY+2*sizeMarginY)/VOXSIZE) 
#define NV  (NVX*NVY)
#define NNX (NVX+1)
#define NNY (NVY+1)
#define NN  (NNX*NNY)
#define NRINC 901

#define MAXNRITER 1000
#define ACCURACY .00001

//parameters for channels distribution
#define IMMOTILITY_CH 1.0*SCALE*SCALE
#define JB	5.0
#define JH	4.0
#define G_NCH 100.0

// cells
#define IMMOTILITY 1.0*SCALE*SCALE						// 1/T
#define NCX 7
#define NCY 7

//fibers
//#define distanceF 20.0									// [mm] distance between fibers
double distanceF;
#define fiberD	0.0025									// [mm] fibers diameter
#define F_DISTANCE rounder(distanceF/VOXSIZE)			// [pixels]
#define F_ANGLE 0										// angle of fibers with horizont

//spreading
//#define GN_CM (70.0/SCALE)								// [/mm] spreading force constant for CM
//#define GN_FB (8.0/SCALE)								// [/mm] for FB
double GN_CM;
double GN_FB;
#define INHIBITION 1.0
#define PART 0.5

//elasticity
//#define TARGETVOLUME_CM  (1.60/1000/VOXSIZE/VOXSIZE) 	// targetvolume [pixels]
//#define TARGETVOLUME_FB  (1.10/1000/VOXSIZE/VOXSIZE)	// targetvolume [pixels]
double TARGETVOLUME_CM;
double TARGETVOLUME_FB;
#define STARTVOLUME (TARGETVOLUME_FB/10)
//#define INELASTICITY_CM 189.0*SCALE*SCALE*SCALE*SCALE 	// [/mm4]
//#define INELASTICITY_FB 62.5*SCALE*SCALE*SCALE*SCALE 	// [/mm4]
double INELASTICITY_CM;
double INELASTICITY_FB;

//nucleus protection
#define NUCLEI_R .007/VOXSIZE			// nucleus radius [pixels]
#define NUCL 2.0						// penalty for nucleus penetration (NUCL * NOSTICKJ)

//Js
//#define NOSTICKJ_CM 1520.0 				// [/mm] contact penalty for none-adhesive surface
//#define NOSTICKJ_FB 1375.0 				// [/mm] contact penalty for none-adhesive surface
double NOSTICKJ_CM;
double NOSTICKJ_FB;
//#define JCMMD (545.0*VOXSIZE)  			// CM-medium
//#define JMDMD (34.4 * VOXSIZE) 			// medium-medium
//#define JFBMD (290.0*VOXSIZE)			// FB-medium
double JMDMD;
double JCMMD;
double JFBMD;
#define JCMCM (0.5*JCMMD) 				// CM-CM
#define JFBFB (0.5*JFBMD)		 		// FB-FB
#define JFBCM (0.8*JCMMD) 				// FB-CM

#define SQ05 .707107 					//sqrt(.5), used often enough to make this convenient

//number of focal adhesions
//#define MAX_FOCALS_CM 13
//#define MAX_FOCALS_FB 16
double MAX_FOCALS_CM;
double MAX_FOCALS_FB;
#define MAX_FOCALS (MAX_FOCALS_CM<MAX_FOCALS_FB ? MAX_FOCALS_FB : MAX_FOCALS_CM)

int silence;

#endif
