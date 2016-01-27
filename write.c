// file: write.c
#include "functions.h"

////////////////////////////////////////////////////////////////////////////////
void write_increment(int increment)
{
	FILE *ofp;

	ofp = fopen("./output/increment_number.out","w");
	fprintf(ofp,"%d",increment);
	fflush(ofp); fclose(ofp);
}


////////////////////////////////////////////////////////////////////////////////
void write_cells(VOX* pv, int increment)
{
	int v;
    int vx,vy;
   	char filename[40];
   	char astring[20];
   	FILE *ofp;

   	myitostr(increment, astring);
	strcpy(filename, "./output/ctags");
   	strcat(filename, astring);
   	strcat(filename, ".out");

	ofp = fopen(filename,"w");
	/*for(v=0; v<NV; v++)
		fprintf(ofp ,"%d\n", pv[v].ctag);*/
    for(vx=0; vx<NVX; vx++) {
        for (vy=0; vy<NVY; vy++) {
            v = vx * NVY + vy;
     		fprintf(ofp ,"%d ", pv[v].ctag);
        }
        fprintf(ofp, "\n");
    }
   	fflush(ofp);  fclose(ofp);
}

////////////////////////////////////////////////////////////////////////////////
void write_contacts(VOX* pv, CONT* contacts, int NRc, int increment)
{
  int v;
    int vx,vy;
    char filename[40];
    char astring[20];
    FILE *ofp;

    myitostr(increment, astring);
  strcpy(filename, "./output/contactM");
    strcat(filename, astring);
    strcat(filename, ".out");

  ofp = fopen(filename,"w");
    for(vx=0; vx<NVX; vx++) {
        for (vy=0; vy<NVY; vy++) {
            v = vx * NVY + vy;
        fprintf(ofp ,"%d ", pv[v].contact);
        }
        fprintf(ofp, "\n");
    }
    fflush(ofp);  fclose(ofp);

    /*strcpy(filename, "./output/contactX");
    strcat(filename, astring);
    strcat(filename, ".out");

  ofp = fopen(filename,"w");
    for(vx=0; vx<NRc; vx++) {
        for (vy=0; vy<MAX_FOCALS; vy++) {
            v = vx*MAX_FOCALS + vy;
        fprintf(ofp ,"%d ", contacts[v].x);
        }
        fprintf(ofp, "\n");
    }
    fflush(ofp);  fclose(ofp);

    strcpy(filename, "./output/contactY");
    strcat(filename, astring);
    strcat(filename, ".out");

  ofp = fopen(filename,"w");
    for(vx=0; vx<NRc; vx++) {
        for (vy=0; vy<MAX_FOCALS; vy++) {
            v = vx*MAX_FOCALS + vy;
        fprintf(ofp ,"%d ", contacts[v].y);
        }
        fprintf(ofp, "\n");
    }
    fflush(ofp);  fclose(ofp);*/
}

////////////////////////////////////////////////////////////////////////////////
void read_cells(VOX* pv, char filename_ctag[40], char filename_cont[40])
{
  int v,k;
  FILE *ofp;

  ofp = fopen(filename_ctag,"r");
    for(v=0; v<NV; v++)
        k = fscanf(ofp ,"%d", &pv[v].ctag);
    fflush(ofp);  fclose(ofp);

    ofp = fopen(filename_cont,"r");
    for(v=0; v<NV; v++)
        k = fscanf(ofp ,"%d", &pv[v].contact);
        
    fflush(ofp);  fclose(ofp);
}
