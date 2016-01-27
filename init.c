// file: init.c
#include "functions.h"

////////////////////////////////////////////////////////////////////////////////
int* alloc_attach(int NRc)
{
	int * attached;

	attached = calloc(NRc+1, sizeof(int));

	for(int i=0;i<NRc+1;i++)
		attached[i]=0;
	
	return attached;
}

////////////////////////////////////////////////////////////////////////////////
VOX* init_voxels(void)
{
	VOX* pv;
	int v, vx, vy;
	int i;

   	pv = calloc(NV, sizeof(VOX));

	// set voxel information
   	for(vy=0; vy<NVY; vy++)
   	for(vx=0; vx<NVX; vx++)
   	{
   		v = vx + vy*NVX;

		//pv[v].x = vx * VOXSIZE; pv[v].y = vy * VOXSIZE;
		pv[v].ctag = 0;
	}
	return pv;
}

////////////////////////////////////////////////////////////////////////////////
int init_cells(VOX* pv)
{
	int v, vx, vy, i, j, ix, iy;
	int NRc;
	double r01;
	double d; int dx, dy,r,dvx,dvy; // distance to center

	NRc = 0;

	dx = (int) (NVX - 2 * MARGIN) / (NCX-1);
	dy = (int) (NVY - 2 * MARGIN) / (NCY-1);
	r  = (int) (sqrt(STARTVOLUME)/2);
	for (iy = 0; iy < NCY; iy++){
		for (ix = 0; ix < NCX; ix++){
			dvx = (mt_random()%(dx-2*r+1)) -((int) dx/2 - r);
			dvy = (mt_random()%(dy-2*r+1)) -((int) dy/2 - r);
			vx = MARGIN + ix * dx + dvx;
			vy = MARGIN + iy * dy + dvy;
			NRc++;
			for(i = -r; i<=r; i++){
				for (j = -r; j<=r; j++){
					v = vx + i + (vy + j)*NVX;
					pv[v].ctag = NRc;
				}
			}
		}	
	}

	return NRc;
}

/////////////////////////////////////////////////////////////////////////////////////

FIELD* set_field (void)
{
	FIELD* pf;
	int n, nx, ny;

   	pf = calloc(NV, sizeof(FIELD));

	// set node information
   	for(ny=0; ny<NVY; ny++)
   	for(nx=0; nx<NVX; nx++)
   	{
   		n = nx + ny*NVX;
		//pf[n].f = FIELD_POWER * cos((2*nx+ny)/F_DISTANCE) + FIELD_POWER_MIN;
		//pf[n].phi = atan(-2)+PI;
		pf[n].f = FIELD_POWER * cos(nx/F_DISTANCE) + FIELD_POWER_MIN;
		pf[n].phi = 0;
	}
	return pf;
}