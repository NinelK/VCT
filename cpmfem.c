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
    shifts=0;
    NCX = 7;
    NCY = 7;

    GN_CM 			= 47.48/SCALE;
    TARGETVOLUME_CM = 2.11/1000/VOXSIZE/VOXSIZE;
    INELASTICITY_CM = 151.37*SCALE*SCALE*SCALE*SCALE;
    DETACH_CM		= 9.89;
            
    GN_FB 			= 26.81/SCALE;
    TARGETVOLUME_FB = 1.39/1000/VOXSIZE/VOXSIZE;
    INELASTICITY_FB = 70.71*SCALE*SCALE*SCALE*SCALE;
    DETACH_FB		= 12.3;
            
    JCMMD 			= 427.82*VOXSIZE;
    JFBMD 			= 306.96*VOXSIZE;
            
    JCMCM 			= 10000.*VOXSIZE;
    JFBFB 			= 10000.*VOXSIZE;
    JFBCM 			= 10000.*VOXSIZE;

    UNLEASH_CM		= 0.0;
	UNLEASH_FB		= 0.0;

	LMAX_CM 		= 66.64/1000/VOXSIZE;
    LMAX_FB 		= 76.7/1000/VOXSIZE;   	

    MAX_FOCALS_CM = 21;
    MAX_FOCALS_FB = 24;

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'p':
        	SEED			= atoi(strtok(optarg, ","));
            NRINC			= atoi(strtok(NULL, ","));          
            break;
        case 's':
        	silence=1;
        	break;
        case 'f':
        	distanceF = 0.010;
        	NCX = 5;
		    NCY = 10;

		    GN_CM 			= 238.22/SCALE;
		    TARGETVOLUME_CM = 1.34/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_CM = 69.88*SCALE*SCALE*SCALE*SCALE;
		    DETACH_CM		= 16.16;
		            
		    GN_FB 			= 9.62/SCALE;
		    TARGETVOLUME_FB = 0.93/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_FB = 68.05*SCALE*SCALE*SCALE*SCALE;
		    DETACH_FB		= 15.20;
		            
		    JCMMD 			= 474.19*VOXSIZE;
		    JFBMD 			= 305.80*VOXSIZE;
		            
		    JCMCM 			= 10000.*VOXSIZE;
		    JFBFB 			= 10000.*VOXSIZE;
		    JFBCM 			= 10000.*VOXSIZE;

		    UNLEASH_CM		= 28.15;
			UNLEASH_FB		= 1.44;

			LMAX_CM 		= 42.31/1000/VOXSIZE;
		    LMAX_FB 		= 48.72/1000/VOXSIZE;   	

		    MAX_FOCALS_CM = 10;
		    MAX_FOCALS_FB = 22;

        	break;
        case 'm':
        	shifts = 1;
        	break;
        default:
            printf("WTF?");
            break;
        }
    }

    if(shifts==1){
    	if(distanceF>1.0){
			
			NCX = 27;
		    NCY = 27;

		    GN_CM 			= 100.0/SCALE;
		 	TARGETVOLUME_CM = 0.9/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_CM = 60.0*SCALE*SCALE*SCALE*SCALE;
		    DETACH_CM		= 11.0;
		            
		    GN_FB 			= 20.0/SCALE;
		    TARGETVOLUME_FB = 0.8/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_FB = 20.0*SCALE*SCALE*SCALE*SCALE;
		    DETACH_FB		= 10.0;
		            
		    JCMMD 			= 600.0*VOXSIZE;
		    JFBMD 			= 275.0*VOXSIZE;
		            
		    JCMCM 			= 700.0*VOXSIZE;
		    JFBFB 			= 500.0*VOXSIZE;
		    JFBCM 			= 700.0*VOXSIZE;

		    UNLEASH_CM		= 0.0;
			UNLEASH_FB		= 0.0;

			LMAX_CM 		= 40.0/1000/VOXSIZE;
		    LMAX_FB 		= 40.0/1000/VOXSIZE;   	

		    MAX_FOCALS_CM = 14;
		    MAX_FOCALS_FB = 8;
		 //    GN_CM 			= 51.03/SCALE;
		 //    TARGETVOLUME_CM = 0.88/1000/VOXSIZE/VOXSIZE;
		 //    INELASTICITY_CM = 62.32*SCALE*SCALE*SCALE*SCALE;
		 //    DETACH_CM		= 30.93;
		            
		 //    GN_FB 			= 5.09/SCALE;
		 //    TARGETVOLUME_FB = 0.79/1000/VOXSIZE/VOXSIZE;
		 //    INELASTICITY_FB = 17.91*SCALE*SCALE*SCALE*SCALE;
		 //    DETACH_FB		= 11.22;
		            
		 //    JCMMD 			= 1013.93*VOXSIZE;
		 //    JFBMD 			= 445.77*VOXSIZE;
		            
		 //    JCMCM 			= 798.73*VOXSIZE;
		 //    JFBFB 			= 473.28*VOXSIZE;
		 //    JFBCM 			= 949.22*VOXSIZE;

		 //    UNLEASH_CM		= 0.0;
			// UNLEASH_FB		= 0.0;

			// LMAX_CM 		= 81.41/1000/VOXSIZE;
		 //    LMAX_FB 		= 73.62/1000/VOXSIZE;   	

		 //    MAX_FOCALS_CM = 12;
		 //    MAX_FOCALS_FB = 13;

    	}else{
    		NCX = 17;
		    NCY = 68;

		    GN_CM 			= 461.36/SCALE;
		    TARGETVOLUME_CM = 0.6/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_CM = 26.42*SCALE*SCALE*SCALE*SCALE;
		    DETACH_CM		= 155.62;
		            
		    GN_FB 			= 233.76/SCALE;
		    TARGETVOLUME_FB = 0.35/1000/VOXSIZE/VOXSIZE;
		    INELASTICITY_FB = 14.24*SCALE*SCALE*SCALE*SCALE;
		    DETACH_FB		= 53.21;
		            
		    JCMMD 			= 937.13*VOXSIZE;
		    JFBMD 			= 560.27*VOXSIZE;
		            
		    JCMCM 			= 631.42*VOXSIZE;
		    JFBFB 			= 267.25*VOXSIZE;
		    JFBCM 			= 1152.05*VOXSIZE;

		    UNLEASH_CM		= 117.94;
			UNLEASH_FB		= 66.93;

			LMAX_CM 		= 62.37/1000/VOXSIZE;
		    LMAX_FB 		= 65.05/1000/VOXSIZE;   	

		    MAX_FOCALS_CM = 8;
		    MAX_FOCALS_FB = 9;
    	}
    }
    
    NCX *= 6;
    NCY *= 6;
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
		printf("DETACH_CM = %.2f\n",DETACH_CM*SCALE);
		printf("\n");
		printf("GN_FB = %.2f\n",GN_FB*SCALE);
		printf("TARGETVOLUME_FB = %.2f\n",TARGETVOLUME_FB*1000*VOXSIZE*VOXSIZE);
		printf("INELASTICITY_FB = %.2f\n",INELASTICITY_FB/(SCALE*SCALE*SCALE*SCALE));
		printf("DETACH_FB = %.2f\n",DETACH_FB*SCALE);
		printf("\n");
		printf("JMDMD = %.3f\n",JMDMD/VOXSIZE);
		printf("JCMMD = %.3f\n",JCMMD/VOXSIZE);
		printf("JFBMD = %.3f\n",JFBMD/VOXSIZE);
		printf("\n");
		printf("JCMCM = %.3f\n",JCMCM/VOXSIZE);
		printf("JFBFB = %.3f\n",JFBFB/VOXSIZE);
		printf("JFBCM = %.3f\n",JFBCM/VOXSIZE);
		printf("\n");
		printf("UNLEASH_CM = %.2f\n",UNLEASH_CM*SCALE);
		printf("UNLEASH_FB = %.2f\n",UNLEASH_FB*SCALE);
		printf("\n");
		printf("LMAX_CM = %.2f px\n",LMAX_CM);
		printf("LMAX_FB = %.2f px\n",LMAX_FB);
		printf("\n");
		printf("MAX_FOCALS_CM = %.2f\n",MAX_FOCALS_CM);
		printf("MAX_FOCALS_FB = %.2f\n",MAX_FOCALS_FB);
	}

	/// INITIALIZE ///
   	srand(SEED); mt_init();
   	pv = init_voxels();
	pf = set_fibers();
	BOX * pb = allocBOX(NCX*NCY+1);

	write_fibers(pf);

	startincr = 0;
	types = calloc((NCX*NCY+1), sizeof(int));
	NRc = init_cells(pv,types,pb);write_cells(pv,0);
	csize = calloc(NRc, sizeof(int)); for(c=0;c<NRc;c++) {csize[c]=0;}
	for(v=0;v<NV;v++) {if(pv[v].ctag) {csize[pv[v].ctag-1]++;}}

	CM* CMs = allocCM(NRc);
	int* attached = alloc_attach(NRc);

	short * CCAlabels = malloc(NV * sizeof(short));

	gettimeofday(&tv, NULL);
	time = tv.tv_sec;

	write_types(types,NRc);		//save types into file

	// START SIMULATION ///
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 500 == 0){
			if(!silence)
				printf("\nSTART INCREMENT %d",incr);
			write_cells(pv,incr);
			write_contacts(pv,incr);
		}

		findCM(pv,CMs,NRc);
		acceptance = CPM_moves(pv,CCAlabels,pb,pf,CMs, 
attached,csize);

		if (incr % 500 == 0 && !silence){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	if(!silence)
	printf("\nSIMULATION FINISHED!\n");

	write_contacts(pv,0);

	/*pv = init_voxels();
	read_cells(pv,types, NRc, "./output/ctags1.sout","./output/conts1.sout","./output/types.sout");*/

	/// START DISTRIBUTION ///
	findCM(pv,CMs,NRc);
	for(incr=startincr; incr<NRINC_CH; incr++)
	{
		if (incr % 100 == 0){
			if(!silence)
				printf("\nSTART CHANNEL DISTRIBUTION %d",incr);
			write_contacts(pv,incr+1);
		}

		acceptance = CH_moves(pv, CMs, 0.5 + 0.5*incr/NRINC);

		if (incr % 100 == 0 && !silence){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	write_cells(pv,1);
	write_contacts(pv,1);

	/// END ///
	if(!silence)
	printf("\nSIMULATION FINISHED!\n");

	gettimeofday(&tv, NULL);
	if(!silence)
	printf("Took %lds\n", tv.tv_sec - time);

	free(pv); 
	free(pf);
	free(CCAlabels);
	
	return 0;
}

