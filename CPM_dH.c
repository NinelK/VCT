// file: cpm_dh.c
#include "functions.h"
#include "math.h"

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
double calcdH(VOX* pv, FIBERS* pf, CM* CMs, CONT* contacts, int* csize, int xt, int xs, int pick, int ttag, int stag)
{
	double dH, dHcontact, dHvol, dHconnectivity, dHfocals, dHnuclei;//, dHstrain;
	int ctag;

	dHcontact = 0;
	dHcontact = calcdHcontact(pv,xt,ttag,stag, pf[xt].Q);

	dHvol = 0;
	dHvol = calcdHvol(csize,ttag,stag);

	dHconnectivity = 0;
	dHconnectivity = calcdHconnectivity(pv,xt,stag);

	dHfocals = 0;
	dHfocals = calcdHfromnuclei(pv, CMs, xt, xs, ttag, stag);

	dHnuclei = 0;
	dHnuclei = calcdHnuclei(pv, CMs, xt, ttag, stag);

	//dHstrain = 0;
	//dHstrain = calcdHstrain(CMs,contacts,xt,stag,ttag);

	dH = dHcontact + dHvol + dHconnectivity + dHfocals + dHnuclei;// + dHstrain;
	return dH;

}


////////////////////////////////////////////////////////////////////////////////
double calcdHcontact(VOX* pv, int xt, int ttag, int stag, int Q)
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
		Hcontact += contactenergy(ttag,nbtag) + scaffoldenergy(ttag, Q);
		Hcontactn += contactenergy(stag,nbtag) + scaffoldenergy(stag, Q);
	}
	dHcontact = Hcontactn-Hcontact;

	return dHcontact;
}

////////////////////////////////////////////////////////////////////////////////
double contactenergy(int tag1, int tag2)
{
	double J;

	J = 0;
	if(tag1!=tag2)
	{
    	if((tag1==0)||(tag2==0))
        	J = JCM;
    	else
        	J = JCC;
	}

	return J;
}

////////////////////////////////////////////////////////////////////////////////
double scaffoldenergy(int tag, int Q)
{
	double J = Q ? JCF : (tag ? JSC : JSM);

	return J;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHvol(int* csize, int ttag, int stag)
{
	double dHvol,dHvolA,dHvolB,V0,eV,eVn;
	int V;

	// assume 2 cells, A (ttag) and B (stag) are involved
	dHvolA=0; dHvolB=0; V0=TARGETVOLUME;
	if(ttag) // cell ttag retracts
	{
		V=csize[ttag-1]; eV=(V-V0)/V0; eVn=(V-1-V0)/V0;
		dHvolA = INELASTICITY*(eVn*eVn-eV*eV);
	}
	if(stag) // cell stag expands
	{
		V=csize[stag-1]; eV=(V-V0)/V0; eVn=(V+1-V0)/V0;
		dHvolB = INELASTICITY*(eVn*eVn-eV*eV);
	}
	dHvol = dHvolA+dHvolB;

	return dHvol;
}


////////////////////////////////////////////////////////////////////////////////
double calcdHconnectivity(VOX* pv, int xt, int stag)
{
	double dH = NOSTICKJ;

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
double calcdHfromnuclei(VOX* pv, CM* CMs, int xt, int xs, int ttag, int stag)
{
	double dH = 0;

	//focals don't go back
	if(pv[xt].contact)
		dH = NOSTICKJ;
	
	if(pv[xs].contact)
		dH = G_N*(1/dist(CMs,xt,stag) - 1/dist(CMs,xs,stag));

	return dH;
}

////////////////////////////////////////////////////////////////////////////////
double calcdHnuclei(VOX* pv, CM* CMs, int xt, int ttag, int stag)
{
	double dH = 0;

	//don't touch the nuclei
	if(dist(CMs,xt,ttag)<NUCLEI_R)
		dH = NUCL*NOSTICKJ;

	return dH;
}

double dist(CM* CMs, int xt, int tag)
{
	int xtx, xty;
	xty = xt/NVX; xtx = xt%NVX;
	return sqrt(sqr(xtx - CMs[tag].x)+sqr(xty - CMs[tag].y));
}

double calcdHstrain(CM* CMs, CONT* contacts, int xt, int stag, int ttag)
{
	return calcHstrain(CMs,contacts,xt,stag)-calcHstrain(CMs,contacts,xt,ttag);
}

double calcHstrain(CM* CMs, CONT* contacts, int xt, int tag)
{
	double dH = gS * sqr(dist(CMs,xt,tag));
	double Perp = find_perp(CMs,contacts,xt,tag);

	if(Perp<NVX)
		dH = gS * Perp * dist(CMs,xt,tag);

	if(tag == 0)
		dH = 0;

	return dH;
}

double find_perp(CM* CMs, CONT* contacts, int xt, int tag)
{
	int i;
	double Alpha, Perp, min;

	min = (double) NVX;

	for(i=0;i<MAX_FOCALS;i++){
		Alpha = alpha(CMs,contacts[tag*MAX_FOCALS + i],xt,tag);
		if(Alpha>=0 && Alpha<=1){
			Perp = perp(CMs,contacts[tag*MAX_FOCALS + i],Alpha,xt,tag);
			if(Perp < min)
				min = Perp;
		}

	}

	return min;
}

double perp(CM* CMs, CONT contact, double Alpha, int xt, int tag)
{	
	double dx, dy;
	int xtx, xty;
	xty = xt/NVX; xtx = xt%NVX;

	dx = (xtx - CMs[tag].x) - Alpha*(contact.x - CMs[tag].x);
	dy = (xty - CMs[tag].y) - Alpha*(contact.y - CMs[tag].y);

	return sqrt(sqr(dx)+sqr(dy));
}


double alpha(CM* CMs, CONT contact, int xt, int tag)
{
	int xtx, xty;
	xty = xt/NVX; xtx = xt%NVX;

	return ((xtx - CMs[tag].x)*(contact.x - CMs[tag].x) + (xty - CMs[tag].y)*(contact.y - CMs[tag].y))
	/ (sqr(contact.x - CMs[tag].x) + sqr(contact.y - CMs[tag].y));
}

///////////////////////////////////////////////////////////////////////////
double sqr (double x)
{
	return x*x;
}



