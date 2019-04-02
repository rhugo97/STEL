#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lista_ligada.c"

#define lambda 200
#define dm 0.008

double delta= 0.001;
double maxRep = 0.025;

int main(){
	//initializations
	lista* list;
	int tipo_ev, channels = 0, numberSim = 0, freeChannels=0, packetLost=0, packetsComing=0;
	int cont=0, delays=0;
	double timeEvent=0, c, u;
	int intervals=(maxRep/delta);
	double average=0, sum=0, timeDelay=0;
	lista *queue;
	int delayed=0, secondDelay;	
	double delayedMore=0;
	
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
	
	//list to the queue
	queue=NULL;
		

	//number of samples
	
	printf("Number of Simulations: ");
	scanf("%d", &numberSim);

	printf("Number of channels: ");
	scanf("%d", &channels);
	freeChannels=channels;

	printf("Delayed more than: ");
	scanf("%lf", &delayedMore);
	

	//start of simulations
	for(int i=0; i < numberSim; i++){
		int tmp=0;
		tipo_ev=list->tipo;
		timeEvent=list->tempo;
		list=remover(list);
		
		if(tipo_ev==0){
			int tmp=0;
			u= (double)((unsigned)rand())/((unsigned)RAND_MAX+1);
			c = -log(u) / lambda;
			packetsComing++;
			
			if(freeChannels>0){
				freeChannels--;	
				u= (double)((unsigned)rand())/((unsigned)RAND_MAX+1);

				double d=-dm*log(u);
				list=adicionar(list,1,timeEvent+d);
				sum+=d;
				
			}
			else{
				queue=adicionar(queue,tipo_ev,timeEvent);
				delays++;
				

			}
			list=adicionar(list,0,timeEvent+c);
		}
		else{
			if(queue!=NULL){
				timeDelay +=timeEvent-(queue->tempo);
				if(delayedMore<(timeEvent-(queue->tempo))){
					secondDelay++;
				}
				queue=remover(queue);
				u= (double)((unsigned)rand())/((unsigned)RAND_MAX+1);
				double d=-dm*log(u);
				list=adicionar(list,1,timeEvent+d);
				sum+=d;
				//histogram
				if(d>maxRep){
					tmp = intervals-1;
				}
				else{
					tmp = (int) (d/delta);
				}

		
				histogram[tmp]++;
			}
			else{
				freeChannels++;
			}
		}
		
		


		
		
	
	}
	for(int i=0; i<intervals; i++){
		printf("Value of %d: %d\n", i+1, histogram[i]);
	}
	printf("Probability of delay: %lf\n", ((double)delays/packetsComing)*100);
	printf("Average Delay: %lf\n",((double)timeDelay/numberSim));
	printf("Probability of being delayed more than %lf : %lf \n", delayedMore, ((double)secondDelay/packetsComing)*100);
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
