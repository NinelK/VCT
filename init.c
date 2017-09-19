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
		pv[v].contact = 0;
		pv[v].bond = 0;
	}
	return pv;
}

////////////////////////////////////////////////////////////////////////////////
int init_cells(VOX* pv, int * types, BOX* pb)
{
	int v, vx, vy, i, j, ix, iy;
	int NRc;
	double r01;
	double d;
	double dx, dy,dvx,dvy; // distance to center
	int r;

	NRc = 0;

	dx = (double) (NVX - 2 * MARGINX) / (NCX);
	dy = (double) (NVY - 2 * MARGINY) / (NCY);
	r  = (int) (sqrt(STARTVOLUME)/2);
	if(dx<2*r || dy<2*r)
		printf("Too dense!");
	for (iy = 0; iy < NCY; iy++){
		for (ix = 0; ix < NCX; ix++){
			dvx = (mt_random()%((int) dx-2*r+1)) -(dx/2 - r);
			dvy = (mt_random()%((int) dy-2*r+1)) -(dy/2 - r);
			vx = MARGINX + (int) (((double) ix + 0.5) * dx + shifts*dvx);
			vy = MARGINY + (int) (((double) iy + 0.5) * dy + shifts*dvy);
			NRc++;
			types[NRc] = (PART<(rand()/(double)RAND_MAX) ? 1 : 2);
			pb[NRc].x1 = vx-r;
			pb[NRc].x2 = vx+r;
			pb[NRc].y1 = vy-r;
			pb[NRc].y2 = vy+r;
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

	dx = F_ANGLE!=0    ? F_DISTANCE / sin(F_ANGLE) : 0.0;
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
