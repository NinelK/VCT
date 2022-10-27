// file: cpm_dh.c
#include "functions.h"
#include "math.h"



#define TARGETVOLUME(a) (a==1 ? TARGETVOLUME_CM : TARGETVOLUME_FB)
#define INELASTICITY(a) (a==1 ? INELASTICITY_CM : INELASTICITY_FB)
#define GN(a)			(a==1 ? GN_CM : GN_FB)
#define DETACH(a)		(a==1 ? DETACH_CM : DETACH_FB)
#define UNLEASH(a)		(a==1 ? UNLEASH_CM : UNLEASH_FB)
#define LMAX(a)			(a==1 ? LMAX_CM : LMAX_FB)

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
		if(ttag!=nbtag){
			dHcontact = (pv[nbs[n]].contact && nbtag!=0) ? 0.0 : JH;
			break;
		}
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
	double dH, dHcontact, dHvol, dHfocals, dHsyncytium, dHnuclei;
	int ctag;

	dHcontact = 0;
	dHcontact = calcdHcontact(pv,xt,xs,ttag,stag);

	dHvol = 0;
	dHvol = calcdHvol(csize,ttag,stag,pv[xt].type,pv[xs].type,TARGETVOLUME_CM, TARGETVOLUME_FB, INELASTICITY_CM, INELASTICITY_FB);

	dHfocals = 0;
	dHfocals = calcdHprotrude(pv, CMs, xt, xs, ttag, stag, pf[xt].Q, pf[xs].Q, LMAX_CM, LMAX_FB, GN_CM, GN_FB, UNLEASH_CM, UNLEASH_FB, DETACH_CM, DETACH_FB);

	dHsyncytium = 0;
	if(E_bond)
		dHsyncytium = calcdHsyncytium(pv, CMs, xt,xs,ttag,stag);

	dHnuclei = 0;
	dHnuclei = calcdHnuclei(pv, CMs, xt, ttag, stag, DETACH_CM, DETACH_FB);

	dH = dHcontact + dHvol + dHfocals + dHsyncytium + dHnuclei;
	return dH;

}

////////////////////////////////////////////////////////////////////////////////
double calcdHsyncytium(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag)
{
	double dH = 0;
	double bondS, bondT;
	int xb, xsy, xsx, xby, xbx, btag, vx, vy;
	double normX, normB;

	if(pv[xs].bond!=0){

		xsy = xs/NVX - CMs[stag].y; xsx = (xs%NVX) - CMs[stag].x;
		
		xb = pv[xs].bond;
		btag = pv[xb].ctag;
		xby = xb/NVX - CMs[btag].y; xbx = (xb%NVX) - CMs[btag].x;

		normX = sqrt(xsy*xsy+xsx*xsx);
		normB = sqrt(xby*xby+xbx*xbx);

		vx = xsx/normX + xbx/normB;
		vy = xsy/normX + xby/normB;
		
		dH += E_bond * (2 - sqrt(vx*vx+vy*vy));

	}

	if(pv[xt].bond!=0){

		xsy = xt/NVX - CMs[ttag].y; xsx = (xt%NVX) - CMs[ttag].x;
		
		xb = pv[xt].bond;
		btag = pv[xb].ctag;
		xby = xb/NVX - CMs[btag].y; xbx = (xb%NVX) - CMs[btag].x;

		normX = sqrt(xsy*xsy+xsx*xsx);
		normB = sqrt(xby*xby+xbx*xbx);

		vx = xsx/normX + xbx/normB;
		vy = xsy/normX + xby/normB;
		
		dH += E_bond * (2 - sqrt(vx*vx+vy*vy));

	}

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
		Hcontact += contactenergy(ttag,nbtag,pv[xt].type,pv[nbs[n]].type,JCMCM,JFBFB,JFBCM,JCMMD,JFBMD);
		Hcontactn += contactenergy(stag,nbtag,pv[xs].type,pv[nbs[n]].type,JCMCM,JFBFB,JFBCM,JCMMD,JFBMD);
	}
	dHcontact = Hcontactn-Hcontact;

	return dHcontact;
}

////////////////////////////////////////////////////////////////////////////////
double contactenergy(int tag1, int tag2, int type1, int type2, double JCMCM, double JCMMD, double JFBFB, double JFBMD,  double JFBCM)
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

	return J;

	// J = 0;
	// if(tag1!=tag2)
	// {
 //    	if((tag1==0)||(tag2==0)){
 //        	type = (tag1==0 ? type2 : type1);
 //        	J = (type==1 ? JCMMD : JFBMD);
 //        }
 //    	else
 //    		if(type1==type2)
 //    			if(cont1 && cont2)
 //    				J = (type1==1 ? JCMCMc : JFBFBc);
 //    			else 
 //    				J = (type1==1 ? JCMCM : JFBFB);
 //    		else
 //    			if(cont1 && cont2)
 //    				J = JFBCMc;
 //    			else
 //        			J = JFBCM;
	// }

	// return J;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHvol(int* csize, int ttag, int stag, int ttype, int stype, double TARGETVOLUME_CM, double TARGETVOLUME_FB, double INELASTICITY_CM, double INELASTICITY_FB )
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
double calcdHprotrude(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag, int Qt, int Qs, double LMAX_CM, double LMAX_FB, double GN_CM, double GN_FB, double UNLEASH_CM, double UNLEASH_FB, double DETACH_CM, double DETACH_FB)
{
	double dH = 0;
	double cost = 1.0, coss = 1.0;
	double distt, dists;
	int xty, xtx;

	if(Qs && Qt){																		//if we move along the fiber -- apply projection
		xty = xs/NVX; xtx = xs%NVX;
		coss = cos(F_ANGLE - atan((xty - CMs[stag].y)/(xtx - CMs[stag].x)));
		xty = xt/NVX; xtx = xt%NVX;
		cost = cos(F_ANGLE - atan((xty - CMs[stag].y)/(xtx - CMs[stag].x)));
	}

	if(pv[xs].contact){
		
		distt = dist(CMs,xt,stag);
		dists = dist(CMs,xs,stag);
		dH = GN(pv[xs].type)*( 	(distt < LMAX(pv[xs].type) ? 1/distt : INF)	*fabs(1/cost) - 
								(dists < LMAX(pv[xs].type) ? 1/dists : 0)	*fabs(1/coss)
							);															//protrusions grow up to LMAX, then have to stop or be erased
		if(pv[xt].contact)
			dH += DETACH(pv[xt].type);													//if we copy one contact over the other, it means that we detach target focal adhesion
		
		if(Qs && !Qt)
			dH += UNLEASH(pv[xs].type);
	}else{
		//focals can be erased with the penalty
		if(pv[xt].contact)	
			dH = DETACH(pv[xt].type);
		else
			dH = 0;																		//if source and target are both not focals
		if(pv[xt].contact && pv[xt].type==0)
			printf("Media contact!!!!");
	}

	return dH;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHnuclei(VOX* pv, CM* CMs, int xt, int ttag, int stag, double DETACH_CM, double DETACH_FB)
{
	double dH = 0;

	//don't touch the nuclei
	if(ttag && dist(CMs,xt,ttag)<NUCLEI_R)
		dH = NUCL*DETACH(pv[xt].type);

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



