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
	lista* list;
	int tipo_ev;
	double timeEvent=0, c, u;
	int intervals=(maxRep/delta);
	double average=0, sum=0;

	/*if(tmpNbins - (int) tmpNbins > 0){
		tmpNbins+= 1;
	}*/
	int histogram[intervals];
	
	for(int i=0; i<intervals; i++){
		histogram[i]=0;
	}
	// random number generator
	time_t t;
	srand((unsigned)time(&t));
	
	//Initialize the list
	list=NULL;
	list=adicionar(list,0,0);
	
	//number of samples
	int numberSim = 0;
	printf("Number of Simulations: ");
	scanf("%d", &numberSim);
	

	//start of simulations
	for(int i=0; i < numberSim; i++){
		

		int tmp=0;
		u= (double)((unsigned)rand())/((unsigned)RAND_MAX+1);
		c = -log(u) / lambda;
		sum +=c;
		list=adicionar(list,0,c);
		//printf("C= %lf\n", c);
	
		
		
		//histogram
		if(c>maxRep){
			tmp = intervals-1;
		}
		else{
			tmp = (int) (c/delta);
		}

		
		histogram[tmp]++;
		
	
	}
	for(int i=0; i<intervals; i++){
		printf("Value of %d: %d\n", i+1, histogram[i]);
	}
	average = sum/numberSim;
	printf("Average : %lf\n", average);
	//imprimir(list);
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
