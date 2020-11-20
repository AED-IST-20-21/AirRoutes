
#include "Zero.h"

#include <stdbool.h>

static int Err

void LControl (FILE *entryfp, FILE *outputfp, struct PBArg *Arg)
{
	int BG,AC;
	
	if (Arg->vi<0) Err=1;
	
	switch(AC=ArgCheck(Arg))
	{
		case 1:
		{
			BG=AZero(entryfp,outputfp,Arg);
			break;
		}
		case 2:
		{
			BG=BZero(entryfp,outputfp,Arg);
			break;
		}
		case 3:
		{
			BG=CZero(entryfp,outputfp,Arg);
			break;
		}
		case 4:
		{
			BG=DZero(entryfp,outputfp,Arg);
			break;
		
		}
		case 5:
		default:
		{
		
			ErrExit(2);
			return;
		}
	}
	
	 if (BG<0){
		BadGraph(entryfp,Arg,AC);
	}
	free(Arg);
	return;
}

void BadGraph(FILE *fp,struct PBArg *Arg,int AC){
	
	int temp1,temp2;
	double temp3;
	
	while (fscanf(fp," %d %d %lf",&temp1, &temp2, &temp3)==3){
	
	}
	if (AC==2){
	fprintf(outputfp,"%d %d %s %d %d -1\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj);
	} else
	fprintf(outputfp,"%d %d %s %d -1\n\n",Arg->v,Arg->e,Arg->var,Arg->vi);
	return;
}

/**************************************
 * Function to determine the degree while reading an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
int AZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg){
	
	int k=0,g=0;
	struct edge *aux;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
		
		if ((aux = EdgeRead(entryfp,aux))==NULL) return -1;
		if ((EdgeCheck(Arg->v,aux))<0){
			
			free(aux);
			return -1;
		}
		
		if ((aux->vi==Arg->vi)||(aux->vj==Arg->vi))
			g++;
		
		k++;
	} while (k < Arg->e);
	
	if (g<=0) g=-1;
	
	/*printf("%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, g);*/
	fprintf(outputfp,"%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, g);
	
	free(aux);

	return 0;
}

/**************************************
 * Function to determine if there is an edge between 2 vertices while reading from an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
 
int BZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct edge *aux;
	short int Flag=0;
	int k=0;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	while (k<Arg->e){
		
		if ((aux = EdgeRead(entryfp,aux))==NULL) return -1;
		if ((EdgeCheck(Arg->v,aux))<0){
			
			free(aux);
			return -1;
		}
		
		if ((((aux->vi==Arg->vi)&&(aux->vj==Arg->vj))||((aux->vj==Arg->vi)&&(aux->vi==Arg->vj))) && (Flag==0)){
			
			Flag=1;
			/*printf("%d %d %s %d %.2f\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,aux->cost);*/
			
		}
		k++;
	}
	if (Flag==0){
		/*printf("%d %d %s %d doesn't exist\n\n",Arg->v,Arg->e,Arg->var,Arg->vi);*/
		fprintf(outputfp,"%d %d %s %d %d -1\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj);
	}
	free(aux);
	
	return 0;
}

int CZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;

	if(G = LGRead(entryfp, Arg))==NULL){
		return -1;
	}
	
	lenght=LenghtList(G->vertice[Arg->vi-1]);
	lamps=LampsInit(G->vertice[Arg->vi-1],lenght);
	
	
	for (i=0;(c==0)&&(i<lenght);i++){
		
		c+=ClickFind(G->vertice[lamps[i]-1],lamps,lenght,i);
		
	}
	
	free(lamps);
	LGFree(G);
	
	return 0;
}

int DZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;
	
	if(G = LGRead(entryfp, Arg))==NULL){
		return -1;
	}
	
	lenght=LenghtList(G->vertice[Arg->vi-1]);
	lamps=LampsInit(G->vertice[Arg->vi-1],lenght);
	
	
	for (i=0;(i<lenght);i++){
		
		c+=ClickFind(G->vertice[lamps[i]-1],lamps,lenght,i);
		
	}

	free(lamps);
	LGFree(G);
	return c;
}

int *LampsInit(struct list *lvi,int lenght){
	
	int *lamps,i;
	struct list *laux;
	
	if ((lamps = (int *) calloc(lenght,sizeof(int))) == NULL)
		ErrExit(3);
	
	laux=lvi;
	
	for (i=0;i<lenght;i++){
		
		lamps[i]=laux->v;
		
		laux=laux->next;
	}
	return lamps;
}


int ClickFind(struct list *adj,int *lamps,int size,int j){

	int c=0,i;
	struct list *aux;
	
	aux=adj;
	
	while(aux!=NULL){
		for (i=j;i<size;i++){
			if (aux->v==lamps[i]){
			
				c++;
				
			}
		}
		aux=aux->next;
	}
	
	return c;
	
}

void LPrint(struct PBArg *Arg,int h,float cost,int mode){
	if (mode==2){
		if cost!=(0){
		fprintf(outputfp,"%d %d %s %d %d %.2f\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj,cost);
		} else fprintf(outputfp,"%d %d %s %d %d -1\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj);
		
	}else fprintf(outputfp ,"%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi,h);
	return;
	
}

