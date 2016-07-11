#include "functions.h"
#include <sys/time.h>
#include <unistd.h>

static char *options = "p:sf";
static char *program_name;

void parse_options(int argc, char *argv[])
{
    int opt;

    program_name = argv[0];
    silence=0;
    distanceF=20.0;

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
        case 'p':
            IMMOTILITY		= atof(strtok(optarg, ","))*SCALE*SCALE;
            GN_FB 			= atof(strtok(NULL, ","))/SCALE;
            TARGETVOLUME_FB = atof(strtok(NULL, ","))/1000/VOXSIZE/VOXSIZE;
            INELASTICITY_FB = atof(strtok(NULL, ","))*SCALE*SCALE*SCALE*SCALE;
            NOSTICKJ		= atof(strtok(NULL, ","));
            JMDMD 			= atof(strtok(NULL, ","))*NOSTICKJ*VOXSIZE;
            JFBMD 			= atof(strtok(NULL, ","))*NOSTICKJ*VOXSIZE;
            break;
        case 's':
        	silence=1;
        	break;
        case 'f':
        	distanceF = 0.020;
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
		printf("IMMOTILITY = %.2f\n",IMMOTILITY/(SCALE*SCALE));
		printf("GN_FB = %.2f\n",GN_FB*SCALE);
		printf("TARGETVOLUME_FB = %.2f\n",TARGETVOLUME_FB*1000*VOXSIZE*VOXSIZE);
		printf("INELASTICITY_FB = %.2f\n",INELASTICITY_FB/(SCALE*SCALE*SCALE*SCALE));
		printf("NOSTICKJ = %.2f\n",NOSTICKJ*SCALE);
		printf("JMDMD = %.3f\n",JMDMD/(NOSTICKJ*VOXSIZE));
		printf("JFBMD = %.3f\n",JFBMD/(NOSTICKJ*VOXSIZE));
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

	write_types(types,NRc);

	if(!silence)
		for (incr=0; incr<NRc; incr++)
			printf("%d ",types[incr]);

	// START SIMULATION ///
	for(incr=startincr; incr<NRINC; incr++)
	{
		if (incr % 100 == 0){
			if (!silence)
				printf("\nSTART INCREMENT %d",incr);
			write_cells(pv,incr);
			write_contacts(pv,NRc,incr);
		}

		findCM(pv,CMs,NRc);
		acceptance = CPM_moves(pv,pf,CMs, attached,csize, 1.0);

		if (!silence && incr % 100 == 0){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	if(!silence)
		printf("\nSIMULATION FINISHED!\n");

	/*// free(pv);
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
			write_contacts(pv,NRc,incr+1);
		}

		acceptance = CH_moves(pv, CMs, 0.5 + 0.5*incr/NRINC);

		if (incr % 100 == 0){
			printf("\nAcceptance rate %.4f",acceptance);
		}
	}

	/// END ///
	printf("\nSIMULATION FINISHED!\n");*/

	gettimeofday(&tv, NULL);
	if(!silence)
		printf("Took %lds\n", tv.tv_sec - time);

	free(pv); 
	free(pf);
	return 0;
}

