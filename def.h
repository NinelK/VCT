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
#define sizeX 0.8 				// [mm]
#define sizeY 0.8 				// [mm]
#define sizeMarginX 0.100 		// [mm] from one side
#define sizeMarginY 0.100 		// [mm] from one side
#define MARGINX rounder(sizeMarginX/VOXSIZE)
#define MARGINY rounder(sizeMarginY/VOXSIZE)
#define NVX rounder((sizeX+2*sizeMarginX)/VOXSIZE) 
#define NVY rounder((sizeY+2*sizeMarginY)/VOXSIZE) 
#define NV  (NVX*NVY)
//#define NRINC 901
int NRINC;

#define MAXNRITER 1000
#define ACCURACY .00001

//parameters for channels distribution
#define IMMOTILITY_CH 1.0*SCALE*SCALE
#define JB	10.0
#define JH	2.0
#define G_NCH 50.0

// cells
#define IMMOTILITY 1.0*SCALE*SCALE						// 1/T
int NCX;
int NCY;

//fibers
//#define distanceF 20.0									// [mm] distance between fibers
double distanceF;
#define fiberD	0.0025									// [mm] fibers diameter
#define F_DISTANCE rounder(distanceF/VOXSIZE)			// [pixels]
#define F_ANGLE 0										// angle of fibers with horizont

//spreading
double GN_CM;
double GN_FB;
double INHIBITION;
#define PART 0.5 			//% FBs

//elasticity
double TARGETVOLUME_CM;
double TARGETVOLUME_FB;
#define STARTVOLUME (TARGETVOLUME_FB/10)
double INELASTICITY_CM;
double INELASTICITY_FB;
double LMAX_CM;
double LMAX_FB;

//nucleus protection
#define NUCLEI_R .007/VOXSIZE			// nucleus radius [pixels]
#define NUCL 2.0						// penalty for nucleus penetration (NUCL * NOSTICKJ)

//Js
double NOSTICKJ_CM;
double NOSTICKJ_FB;
double JMDMD;
double JCMMD;
double JFBMD;
double JCMCM;
double JFBFB;
double JFBCM;

double UNLEASH_CM;
double UNLEASH_FB;

#define SQ05 .707107 					//sqrt(.5), used often enough to make this convenient

//number of focal adhesions
double MAX_FOCALS_CM;
double MAX_FOCALS_FB;

int silence;
int shifts;

#endif
