// file: structures.h
#ifndef _STRUCTURE
#define _STRUCTURE
#include <stdlib.h>
#include "def.h"

typedef struct
{
   	//double x, y;			// minimum coordinates
	int ctag;				// id of occupying cell, 0 if no cell
	int contact;			// 0 or 1
} VOX;

typedef struct
{
	double f;				//force
	double phi;				//direction
} FIELD;

typedef struct
{
	double x;
	double y;
} CM;

typedef struct
{
	int x;
	int y;
} CONT;

#endif
