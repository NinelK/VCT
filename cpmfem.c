#include "functions.h"
#include <sys/time.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

static char *options = "p:smfc";
static char *program_name;

void parse_options(int argc, char *argv[])
{
    int opt;

    program_name = argv[0];
    silence=0;
    distanceF=20.0;
    shifts=0;
    CONT = 0;
    CONT_INHIB = 1;
    #include "conf/cnfgSN.cfg"

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

        	#include "conf/cnfgSF.cfg"

        	break;
        case 'm':
        	shifts = 1;
        	break;
        case 'c':			//move contacts if they are under the cell. If CONT=0, then only contacts on the perifery move.
        	CONT = 1;			//switches on movement of the attachment sites under the cell, not only on the periphery
        	CONT_INHIB = 0;		//switches off simple variant of contact inhibitio, when the cell just does not create new attachment sites when it is facing a neighbouring cell there
        						//these two properties can be separated. In "Virtual cardiac monolayers..." we used 		CONT = 0, CONT_INHIB = 1
        						//for pathways formation we changes the idea behind contact inhibition, so we switched to 	CONT = 1, CONT_INHIB = 0
        	break;
        default:
            printf("Wrong parameter");
            break;
        }
    }

    if(shifts==1)
    	if(distanceF>1.0){
		    #include "conf/cnfgMN.cfg"
    	}
    	else{
    		#include "conf/cnfgMF.cfg"
    	}
    
    NCX *= MULT;
    NCY *= MULT;
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

		if (incr % STEP_PRINT == 0){
			if(!silence)
				printf("\nSTART INCREMENT %d",incr);
			write_cells(pv,incr);
			write_contacts(pv,incr);
		}

		findCM(pv,CMs,NRc);
		acceptance = CPM_moves(pv,CCAlabels,pb,pf,CMs, 
attached,csize);

		if (incr % STEP_PRINT == 0 && !silence){
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

