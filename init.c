// file: init.c
#include "functions.h"

////////////////////////////////////////////////////////////////////////////////
int* alloc_attach(int NRc)
{
	int i;
	int * attached;

	attached = calloc(NRc+1, sizeof(int));

	for(i=0;i<NRc+1;i++)
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
		pv[v].type = 0;
	}
	return pv;
}

////////////////////////////////////////////////////////////////////////////////
int init_cells(VOX* pv, int * types)
{
	int v, vx, vy, i, j, ix, iy;
	int NRc;
	double r01;
	double d; int dx, dy,r,dvx,dvy; // distance to center

	NRc = 0;

	dx = (int) (NVX - 2 * MARGINX) / (NCX-1);
	dy = (int) (NVY - 2 * MARGINY) / (NCY-1);
	r  = (int) (sqrt(STARTVOLUME)/2);
	for (iy = 0; iy < NCY; iy++){
		for (ix = 0; ix < NCX; ix++){
			dvx = (mt_random()%(dx-2*r+1)) -((int) dx/2 - r);
			dvy = (mt_random()%(dy-2*r+1)) -((int) dy/2 - r);
			vx = MARGINX + ix * dx + 0*dvx;
			vy = MARGINY + iy * dy + 0*dvy;
			NRc++;
			types[NRc] = (PART<(rand()/(double)RAND_MAX) ? 1 : 2);
			for(i = -r; i<=r; i++){
				for (j = -r; j<=r; j++){
					v = vx + i + (vy + j)*NVX;
					if (v<NV){
						pv[v].ctag = NRc;
						pv[v].type = types[NRc]; 
					}
					else
						printf("Cell out of area: (%d,%d)\n",vx+i-NVX,vy+j-NVY);
				}
			}
		}	
	}

	return NRc;
}

////////////////////////////////////////////////////////////////////////////////
FIBERS* set_fibers(void)
{
	FIBERS* pf;
	int v, vx, vy, vd, fd, kc;
	int i;
	double dx,dy;
	double k, k0;

	dx = F_ANGLE!=0 ? F_DISTANCE / sin(F_ANGLE) : 0.0;
	dy = F_ANGLE!=PI/2 ? F_DISTANCE / cos(F_ANGLE) : 0.0;

   	pf = calloc(NV, sizeof(FIBERS));

	// set voxel information
   	for(v=0; v<NV; v++)
   		pf[v].Q = 0;

   	if(F_ANGLE!=PI/2){
   		fd = round(fiberD / VOXSIZE / cos(F_ANGLE));
	   	fd = fd<1 ? 1 : fd;
	   	for(vx=0; vx<NVX; vx++){
	   		k0 = fmod(vx*tan(F_ANGLE),dy);
	   		k = k0;
	   		for(vy=0; vy<=(NVY-k0)/dy; vy++){
	   			for(vd=0; vd<fd; vd++){
	   				kc = round(k)+vd;
	   				v = vx + kc*NVX;
	   				if(kc<NVY)
	   					pf[v].Q = 1;
	   			}
	   			k += dy;
	   		}
	   	}
	}

	if(F_ANGLE!=0){
		fd = round(fiberD / VOXSIZE / sin(F_ANGLE));
	   	fd = fd<1 ? 1: fd;
	   	printf("fiberdX: %d\n", fd);
	   	for(vy=0; vy<NVY; vy++){
	   		k0 = fmod(vy/tan(F_ANGLE),dx);
	   		k = k0;
	   		for(vx=0; vx<=(NVX-k0)/dx; vx++){
	   			for(vd=0; vd<fd; vd++){
	   				kc = round(k)+vd;
		   			v = kc + vy*NVX;
		   			if(kc<NVX)
		   				pf[v].Q = 1;
	   			}
	   			k += dx;
	   		}
	   	}
	}

	return pf;
}
