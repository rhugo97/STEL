#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lista_ligada.c"

#define lambda 8.0

double delta = (double)(1.0/lambda)/5;
double maxRep = 5* (1/lambda);

int main(){
	//initializations
	//lista* list;
	int tipo_ev;
	double nDelta = (1.0/1000);
	double p= lambda*delta;
	double timeEvent=0, c, u, currentE=0, lastE=0;
	int intervals=maxRep/delta;
	double average=0, sum=0;

	int histogram[intervals];
	
	for(int i=0; i<intervals; i++){
		histogram[i]=0;
	}
	// random number generator
	time_t t;
	srand((unsigned)time(&t));
	
	//number of samples
	int numberSim = 0;
	printf("Number of Simulations: ");
	scanf("%d", &numberSim);
	printf("\n");
	
	
	//start of simulations
	for(int i=0; i < numberSim; i++){
		
		u=1;
		timeEvent=0;
		int tmp=0;
		while(u>nDelta*lambda){
			u= (double)((unsigned)rand())/((unsigned)RAND_MAX+1);
			timeEvent = timeEvent+nDelta;

		}
		
		if(timeEvent>maxRep){
			tmp= intervals-1;
		}
		else{
			tmp=timeEvent/delta;
		}
		
		average = ((average*i) + timeEvent) / (i+1);
		histogram[tmp]++;
		
	
	}
	for(int i=0; i<intervals; i++){
		printf("Value of %d: %d\n", i+1, histogram[i]);
	}
	
	printf("Average : %lf\n", average);
	//send to excel
	FILE *fp;
	fp=fopen("histdata.xsl","w");
	for(int i=0; i<intervals; i++){
		fprintf(fp,"%d,",histogram[i]);
	}
	fprintf(fp,"\n");
	for(int i=0;i<intervals; i++){
		fprintf(fp,"%d,",i);
	}
	
	fclose(fp);

	

}
