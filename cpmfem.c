#include "functions.h"
#include <sys/time.h>
#include <unistd.h>
#include <getopt.h>

static char *options = "p:smf";
static char *program_name;

void parse_options(int argc, char *argv[])
{
    int opt;

    program_name = argv[0];
    silence=0;
    distanceF=20.0;
    NCX = 7;
    NCY = 7;

    GN_CM 			= 75.32/SCALE;
    TARGETVOLUME_CM = 1.93/1000/VOXSIZE/VOXSIZE;
    INELASTICITY_CM = 202.9*SCALE*SCALE*SCALE*SCALE;
    NOSTICKJ_CM		= 938.0;
            
    GN_FB 			= 4.74/SCALE;
    TARGETVOLUME_FB = 1.32/1000/VOXSIZE/VOXSIZE;
    INELASTICITY_FB = 99.5*SCALE*SCALE*SCALE*SCALE;
    NOSTICKJ_FB		= 949.4;
            
    JMDMD 			= 33.0*VOXSIZE;
    JCMMD 			= 418.7*VOXSIZE;
    JFBMD 			= 211.1*VOXSIZE;
            
    /*JCMCM 			= 0.*VOXSIZE;
    JFBFB 			= 0.*VOXSIZE;
    JFBCM 			= 0.*VOXSIZE;

    UNLEASH_CM		= 0.;
    UNLEASH_FB		= 0.;

    INHIBITION 		= 1.;*/

    MAX_FOCALS_CM = 13;
    MAX_FOCALS_FB = 16;

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'p':
        	SEED			= atoi(strtok(optarg, ","));
            
            break;
        case 's':
        	silence=1;
        	break;
        case 'f':
        	distanceF = 0.010;

        	NCX = 5;
    		NCY = 10;

    		GN_CM 			= 115.61/SCALE;
    		TARGETVOLUME_CM = 1.11/1000/VOXSIZE/VOXSIZE;
    		INELASTICITY_CM = 88.7*SCALE*SCALE*SCALE*SCALE;
    		NOSTICKJ_CM		= 990.4;
            
    		GN_FB 			= 2.80/SCALE;
    		TARGETVOLUME_FB = 0.83/1000/VOXSIZE/VOXSIZE;
    		INELASTICITY_FB = 109.8*SCALE*SCALE*SCALE*SCALE;
    		NOSTICKJ_FB		= 918.4;
            
    		JMDMD 			= 25.0*VOXSIZE;
    		JCMMD 			= 304.4*VOXSIZE;
    		JFBMD 			= 126.0*VOXSIZE;

    		UNLEASH_CM		= 23.2;
    		UNLEASH_FB		= 8.1;

    		MAX_FOCALS_CM = 7;
    		MAX_FOCALS_FB = 13;
        	break;
        case 'm':
        	if(distanceF>1.0){
        		NCX = 26;
    			NCY = 26;

    			GN_CM 			= 81.42/SCALE;
    			TARGETVOLUME_CM = 0.96/1000/VOXSIZE/VOXSIZE;
    			INELASTICITY_CM = 239.4*SCALE*SCALE*SCALE*SCALE;
    			NOSTICKJ_CM		= 697.4;
            
    			GN_FB 			= 13.46/SCALE;
    			TARGETVOLUME_FB = 0.74/1000/VOXSIZE/VOXSIZE;
    			INELASTICITY_FB = 86.2*SCALE*SCALE*SCALE*SCALE;
    			NOSTICKJ_FB		= 753.0;
            
    			JMDMD 			= 28.36*VOXSIZE;
    			JCMMD 			= 539.9*VOXSIZE;
    			JFBMD 			= 327.5*VOXSIZE;
            
    			JCMCM 			= 715.5*VOXSIZE;
    			JFBFB 			= 375.7*VOXSIZE;
    			JFBCM 			= 557.9*VOXSIZE;

    			INHIBITION 		= 1.41;

    			MAX_FOCALS_CM = 8;
    			MAX_FOCALS_FB = 8;
        	}else{
        		NCX = 16;
    			NCY = 67;

    			GN_CM 			= 110.2/SCALE;
    			TARGETVOLUME_CM = 0.67/1000/VOXSIZE/VOXSIZE;
    			INELASTICITY_CM = 198.9*SCALE*SCALE*SCALE*SCALE;
    			NOSTICKJ_CM		= 794.2;
            
    			GN_FB 			= 29.3/SCALE;
    			TARGETVOLUME_FB = 0.59/1000/VOXSIZE/VOXSIZE;
    			INELASTICITY_FB = 86.8*SCALE*SCALE*SCALE*SCALE;
    			NOSTICKJ_FB		= 992.8;
            
    			JMDMD 			= 28.19*VOXSIZE;
    			JCMMD 			= 631.7*VOXSIZE;
    			JFBMD 			= 283.9*VOXSIZE;
            
    			JCMCM 			= 726.9*VOXSIZE;
    			JFBFB 			= 279.3*VOXSIZE;
    			JFBCM 			= 413.6*VOXSIZE;

    			INHIBITION 		= 1.66;

    			UNLEASH_CM		= 8.6;
    			UNLEASH_FB		= 6.2;

    			MAX_FOCALS_CM = 4;
    			MAX_FOCALS_FB = 5;
        	}
        	break;
        default:
            printf("WTF?");
            break;
        }
    }
}


int main(int argc, char *argv[])
{

	struct timeval tv;
    time_t time;

	int d;
	VOX *pv;
	FIBERS *pf;
	int NRc,c,v;
	int * types;
	int *csize;
	int incr, startincr;
	double acceptance, acceptance_phi;

	parse_options(argc, argv);
	
	if(!silence){
		printf("SEED = %d\n",SEED);
		printf("Sample size = %d x %d\n",NCX,NCY);
		printf("\n");
		printf("GN_CM = %.2f\n",GN_CM*SCALE);
		printf("TARGETVOLUME_CM = %.2f\n",TARGETVOLUME_CM*1000*VOXSIZE*VOXSIZE);
		printf("INELASTICITY_CM = %.2f\n",INELASTICITY_CM/(SCALE*SCALE*SCALE*SCALE));
		printf("NOSTICKJ_CM = %.2f\n",NOSTICKJ_CM*SCALE);
		printf("\n");
		printf("GN_FB = %.2f\n",GN_FB*SCALE);
		printf("TARGETVOLUME_FB = %.2f\n",TARGETVOLUME_FB*1000*VOXSIZE*VOXSIZE);
		printf("INELASTICITY_FB = %.2f\n",INELASTICITY_FB/(SCALE*SCALE*SCALE*SCALE));
		printf("NOSTICKJ_FB = %.2f\n",NOSTICKJ_FB*SCALE);
		printf("\n");
		printf("JMDMD = %.3f\n",JMDMD/VOXSIZE);
		printf("JCMMD = %.3f\n",JCMMD/VOXSIZE);
		printf("JFBMD = %.3f\n",JFBMD/VOXSIZE);
		printf("\n");
		printf("JCMCM = %.3f\n",JCMCM/VOXSIZE);
		printf("JFBFB = %.3f\n",JFBFB/VOXSIZE);
		printf("JFBCM = %.3f\n",JFBCM/VOXSIZE);
		printf("\n");
		printf("INHIBITION = %.3f\n",INHIBITION);
		printf("\n");
		printf("UNLEASH_CM = %.2f\n",UNLEASH_CM*SCALE);
		printf("UNLEASH_FB = %.2f\n",UNLEASH_FB*SCALE);
		printf("\n");
		printf("MAX_FOCALS_CM = %.2f\n",MAX_FOCALS_CM);
		printf("MAX_FOCALS_FB = %.2f\n",MAX_FOCALS_FB);
	}

	/// INITIALIZE ///
   	srand(SEED); mt_init();
   	pv = init_voxels();
	pf = set_fibers();

	write_fibers(pf);

	startincr = 0;
	types = calloc((NCX*NCY+1), sizeof(int));
	NRc = init_cells(pv,types);write_cells(pv,0);
	csize = calloc(NRc, sizeof(int)); for(c=0;c<NRc;c++) {csize[c]=0;}
	for(v=0;v<NV;v++) {if(pv[v].ctag) {csize[pv[v].ctag-1]++;}}

	CM* CMs = allocCM(NRc);
	int* attached = alloc_attach(NRc);

	gettimeofday(&tv, NULL);
	time = tv.tv_sec;

	write_types(types,NRc);		//save types into file

	// START SIMULATION ///
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 100 == 0){
			if(!silence)
				printf("\nSTART INCREMENT %d",incr);
			write_cells(pv,incr);
			write_contacts(pv,NRc,incr);
		}

		findCM(pv,CMs,NRc);
		acceptance = CPM_moves(pv,pf,CMs, attached,csize);

		if (incr % 100 == 0 && !silence){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	if(!silence)
	printf("\nSIMULATION FINISHED!\n");

	// pv = init_voxels();
	// read_cells(pv,"./output/ctags1000.sout","./output/contactM1000.sout");

	/// START DISTRIBUTION ///
	findCM(pv,CMs,NRc);
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 100 == 0){
			if(!silence)
				printf("\nSTART CHANNEL DISTRIBUTION %d",incr);
			write_contacts(pv,NRc,incr+1);
		}

		acceptance = CH_moves(pv, CMs, 0.5 + 0.5*incr/NRINC);

		if (incr % 100 == 0 && !silence){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	if(!silence)
	printf("\nSIMULATION FINISHED!\n");

	gettimeofday(&tv, NULL);
	if(!silence)
	printf("Took %lds\n", tv.tv_sec - time);

	free(pv); 
	free(pf);
	return 0;
}

