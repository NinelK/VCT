// file: cpm_dh.c
#include "functions.h"
#include "math.h"

#define TARGETVOLUME(a) (a==1 ? TARGETVOLUME_CM : TARGETVOLUME_FB)
#define INELASTICITY(a) (a==1 ? INELASTICITY_CM : INELASTICITY_FB)
#define GN(a)			(a==1 ? GN_CM : GN_FB)
#define NOSTICKJ(a)		(a==1 ? NOSTICKJ_CM : NOSTICKJ_FB)
//#define TARGETVOLUME(a) (a==2 ? TARGETVOLUME_FB : TARGETVOLUME_CM)
//#define INELASTICITY(a) (a==2 ? INELASTICITY_FB : INELASTICITY_CM)
//#define GN(a)			(a==2 ? GN_FB : GN_CM)
//#define NOSTICKJ(a)		(a==2 ? NOSTICKJ_FB : NOSTICKJ_CM)

////////////////////////////////////////////////////////////////////////////////
double calcdH_CH(VOX* pv, CM* CMs, int xt, int xs)
{
	double dH, dHdist, dHborder;

	dHborder = 0;
	dHborder = calcdHborder(pv,xt, pv[xt].ctag);

	dHdist = 0;
	dHdist = calcdHdist(pv, CMs, xt, xs, pv[xt].ctag);

	dH = dHdist + dHborder;

	return dH;

}

////////////////////////////////////////////////////////////////////////////////
double calcdHborder(VOX* pv, int xt, int ttag)
{
	double dHcontact = JB;
	int nbs[8],n,nbtag;

	nbs[0]=xt-1+NVX; nbs[1]=xt+NVX; nbs[2]=xt+1+NVX;
	nbs[7]=xt-1;                    nbs[3]=xt+1;
	nbs[6]=xt-1-NVX; nbs[5]=xt-NVX; nbs[4]=xt+1-NVX;
	for(n=0;n<8;n++)
	{
		nbtag = pv[nbs[n]].ctag;
		if(ttag!=nbtag)
			dHcontact = (pv[nbs[n]].contact && nbtag!=0) ? 0.0 : JH;
	}
	
	return dHcontact;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHdist(VOX* pv, CM* CMs, int xt, int xs, int ttag)
{
	double dH = 0;

	if(pv[xs].contact)
		dH = G_NCH/dist(CMs,xt,ttag);

	return dH;
}

////////////////////////////////////////////////////////////////////////////////
double calcdH(VOX* pv, FIBERS* pf, CM* CMs, int* csize, int xt, int xs, int pick, int ttag, int stag)
{
	double dH, dHcontact, dHvol, dHconnectivity, dHfocals, dHnuclei;//, dHstrain;
	int ctag;

	dHcontact = 0;
	dHcontact = calcdHcontact(pv,xt,xs,ttag,stag);

	dHvol = 0;
	dHvol = calcdHvol(csize,ttag,stag,pv[xt].type,pv[xs].type);

	dHconnectivity = 0;
	dHconnectivity = calcdHconnectivity(pv,xt,stag);

	dHfocals = 0;
	dHfocals = calcdHfromnuclei(pv, CMs, xt, xs, ttag, stag, pf[xt].Q, pf[xs].Q);

	dHnuclei = 0;
	dHnuclei = calcdHnuclei(pv, CMs, xt, ttag, stag);

	dH = dHcontact + dHvol + dHconnectivity + dHfocals + dHnuclei;
	return dH;

}


////////////////////////////////////////////////////////////////////////////////
double calcdHcontact(VOX* pv, int xt, int xs, int ttag, int stag)
{
	double dHcontact, Hcontact, Hcontactn;
	int nbs[8],n,nbtag;

	Hcontact=0; Hcontactn=0;
	nbs[0]=xt-1+NVX; nbs[1]=xt+NVX; nbs[2]=xt+1+NVX;
	nbs[7]=xt-1;                    nbs[3]=xt+1;
	nbs[6]=xt-1-NVX; nbs[5]=xt-NVX; nbs[4]=xt+1-NVX;
	for(n=0;n<8;n++)
	{
		nbtag = pv[nbs[n]].ctag;
		Hcontact += contactenergy(ttag,nbtag,pv[xt].type,pv[nbs[n]].type);
		Hcontactn += contactenergy(stag,nbtag,pv[xs].type,pv[nbs[n]].type);
	}
	dHcontact = Hcontactn-Hcontact;

	return dHcontact;
}

////////////////////////////////////////////////////////////////////////////////
double contactenergy(int tag1, int tag2, int type1, int type2)
{
	double J;
	int type;

	J = 0;
	if(tag1!=tag2)
	{
    	if((tag1==0)||(tag2==0)){
        	type = (tag1==0 ? type2 : type1);
        	J = (type==1 ? JCMMD : JFBMD);
        }
    	else
    		if(type1==type2)
    			J = (type1==1 ? JCMCM : JFBFB);
    		else
        		J = JFBCM;
	}

	if(tag1==tag2 && tag1==0)
		J = JMDMD;

	return J;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHvol(int* csize, int ttag, int stag, int ttype, int stype)
{
	double dHvol,dHvolA,dHvolB,V0,eV,eVn;
	int V;

	// assume 2 cells, A (ttag) and B (stag) are involved
	dHvolA=0; dHvolB=0;
	if(ttag) // cell ttag retracts
	{
		V0=TARGETVOLUME(ttype);
		V=csize[ttag-1]; eV=(V-V0)/V0; eVn=(V-1-V0)/V0;
		dHvolA = INELASTICITY(ttype)*(eVn*eVn-eV*eV);
	}
	if(stag) // cell stag expands
	{
		V0=TARGETVOLUME(stype);
		V=csize[stag-1]; eV=(V-V0)/V0; eVn=(V+1-V0)/V0;
		dHvolB = INELASTICITY(stype)*(eVn*eVn-eV*eV);
	}
	dHvol = dHvolA+dHvolB;

	return dHvol;
}


////////////////////////////////////////////////////////////////////////////////
double calcdHconnectivity(VOX* pv, int xt, int stag)
{
	double dH = NOSTICKJ(pv[xt].type);			//if type=0 -- process below (dH=0)

	if(pv[xt].type == 0)						//if you copy something TO media subcell
		dH = 0;									//connectivity never gets worse

	int nbs[4],n;

					 nbs[0]=xt+NVX; 
	nbs[3]=xt-1;                    nbs[1]=xt+1;
					 nbs[2]=xt-NVX; 

	for(n=0;n<4;n++)
		if (pv[nbs[n]].ctag == stag)
			dH = 0;

	return dH;
}

double findphi(CM* CMs, int xt, int tag)
{
	int xtx, xty;
	double phi;
	xty = xt/NVX; xtx = xt%NVX;
	phi = atan((CMs[tag].y - (double) xty)/(CMs[tag].x-(double) xtx));
	if(phi>=PI)
		phi -= PI;
	if(phi<0)
		phi += PI;
	return phi;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHfromnuclei(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag, int Qt, int Qs)
{
	double dH = 0;
	double cost = 1.0, coss = 1.0;
	int xty, xtx;

	xty = xs/NVX; xtx = xs%NVX;

	if(Qs)
		coss = cos(F_ANGLE - atan((xty - CMs[stag].y)/(xtx - CMs[stag].x)));

	xty = xt/NVX; xtx = xt%NVX;

	if(Qt)
		cost = cos(F_ANGLE - atan((xty - CMs[stag].y)/(xtx - CMs[stag].x)));

	if(pv[xs].contact){
		if(pv[xt].contact)
			dH = NOSTICKJ(pv[xs].type) + NOSTICKJ(pv[xt].type);
		else{
			dH = GN(pv[xs].type)*(1/dist(CMs,xt,stag)/cost - 1/dist(CMs,xs,stag)/coss);
			if(ttag!=0)
				dH /= INHIBITION;
		}
	}else{
		//focals can not be erased
		if(pv[xt].contact)	
			dH = NOSTICKJ(pv[xt].type);
		else
			dH = 0;
		if(pv[xt].contact && pv[xt].type==0)
			printf("Media contact!!!!");
	}

	return dH;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHnuclei(VOX* pv, CM* CMs, int xt, int ttag, int stag)
{
	double dH = 0;

	//don't touch the nuclei
	if(ttag && dist(CMs,xt,ttag)<NUCLEI_R)
		dH = NUCL*NOSTICKJ(pv[xt].type);

	return dH;
}

double dist(CM* CMs, int xt, int tag)
{
	int xtx, xty;
	xty = xt/NVX; xtx = xt%NVX;
	return sqrt(sqr(xtx - CMs[tag].x)+sqr(xty - CMs[tag].y));
}

///////////////////////////////////////////////////////////////////////////
double sqr (double x)
{
	return x*x;
}



