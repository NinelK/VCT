#include "functions.h"
#include <sys/time.h>

int main(void)
{

	struct timeval tv;
    time_t time;

	int d;
	VOX *pv;
	FIBERS *pf;
	int NRc,c,v;
	int *csize;
	int incr, startincr;
	double acceptance, acceptance_phi;

	/// INITIALIZE ///
   	srand(SEED); mt_init();
   	pv = init_voxels();
	pf = set_fibers();

	write_fibers(pf);

	startincr = 0;
	NRc = init_cells(pv);write_cells(pv,0);
	csize = calloc(NRc, sizeof(int)); for(c=0;c<NRc;c++) {csize[c]=0;}
	for(v=0;v<NV;v++) {if(pv[v].ctag) {csize[pv[v].ctag-1]++;}}

	CM* CMs = allocCM(NRc);
	CONT* contacts = allocContacts(NRc);
	int* attached = alloc_attach(NRc);

	gettimeofday(&tv, NULL);
	time = tv.tv_sec;

	printf("JCF/JSC: %.4f\n",JCF/JSC);

	// START SIMULATION ///
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 100 == 0){
			printf("\nSTART INCREMENT %d",incr);
			write_cells(pv,incr);
			write_contacts(pv,contacts,NRc,incr);
		}

		findCM(pv,CMs,NRc);
		acceptance = CPM_moves(pv,pf,CMs,contacts, attached,csize);

		if (incr % 100 == 0){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	printf("\nSIMULATION FINISHED!\n");

	// free(pv);
	// pv = init_voxels();
	// read_cells(pv,"./output/ctags1000.sout","./output/contactM1000.sout");
	// incr=800;
	// write_cells(pv,incr);
	// write_contacts(pv,contacts,NRc,incr);

	/// START DISTRIBUTION ///
	findCM(pv,CMs,NRc);
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 100 == 0){
			printf("\nSTART CHANNEL DISTRIBUTION %d",incr);
			write_contacts(pv,contacts,NRc,incr+1);
		}

		acceptance = CH_moves(pv, CMs, 0.5 + 0.5*incr/NRINC);

		if (incr % 100 == 0){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	printf("\nSIMULATION FINISHED!\n");

	gettimeofday(&tv, NULL);
	printf("Took %lds\n", tv.tv_sec - time);

	free(pv); 
	free(pf);
	return 0;
}

