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
	int type;				//id of cell type
	int bond;
} VOX;

typedef struct
{
	double x;
	double y;
} CM;

typedef struct
{
	int Q;
} FIBERS;

typedef struct
{
	int x1;
	int x2;
	int y1;
	int y2;
} BOX;

#endif
