
#include "Zero.h"

#include <stdbool.h>

void LControl (FILE *entryfp, FILE *outputfp, struct PBArg *Arg)
{
	int BG=0,AC=0;
	double cost=0;
	
	switch(AC=ArgCheck(Arg))
	{
		case 1:
		{
			BG=AZero(entryfp,Arg);
			break;
		}
		case 2:
		{
			BG=BZero(entryfp,Arg,&cost);
			break;
		}
		case 3:
		{
			BG=CZero(entryfp,Arg);
			break;
		}
		case 4:
		{
			BG=DZero(entryfp,Arg);
			break;
		
		}
		default:
		{
			Arg->err=1;
			break;
		}
	}
	
	LPrint(outputfp,Arg,BG,cost,AC);
	
	free(Arg);
	return;
}

void BadGraph(FILE *fp){
	
	int temp1,temp2;
	double temp3;
	
	while (fscanf(fp," %d %d %lf",&temp1, &temp2, &temp3)==3){
	
	}
	return;
}

int AZero(FILE *entryfp, struct PBArg *Arg){
	
	int k=0,g=0;
	struct edge *aux;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
		
		if ((aux = EdgeRead(entryfp,aux))==NULL) Arg->err=1;
		if ((EdgeCheck(Arg->v,aux))<0) Arg->err=1;
		
		if ((aux->vi==Arg->vi)||(aux->vj==Arg->vi))
			g++;
		
		k++;
	} while (k < Arg->e);
	
	free(aux);
	
	if (g<=0) Arg->err=1;

	return g;
}

int BZero(FILE *entryfp, struct PBArg *Arg,double* cost)
{
	struct edge *aux;
	short int Flag=0;
	int k=0;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	while (k<Arg->e){
		
		if ((aux = EdgeRead(entryfp,aux))==NULL) Arg->err=1;
		if ((EdgeCheck(Arg->v,aux))<0) Arg->err=1;
		
		if ((((aux->vi==Arg->vi)&&(aux->vj==Arg->vj))||((aux->vj==Arg->vi)&&(aux->vi==Arg->vj))) && (Flag==0)){
			
			Flag=1;
			*cost=aux->cost;
		}
		k++;
	}

	free(aux);
	
	if (Flag==0) Arg->err=1;
	
	return (int) Flag;
}

int CZero(FILE *entryfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;

	if((G = LGRead(entryfp, Arg))==NULL)Arg->err=1;
	
	lenght=LenghtList(G->vertice[Arg->vi-1]);
	lamps=LampsInit(G->vertice[Arg->vi-1],lenght);
	
	
	for (i=0;(c<1)&&(i<lenght);i++){
		
		c+=ClickFind(G->vertice[lamps[i]-1],lamps,lenght,i);
		
	}
	
	free(lamps);
	LGFree(G);
	if (c>0){
		c=1;
	}
	
	return c;
}

int DZero(FILE *entryfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;
	
	if ((G = LGRead(entryfp, Arg))==NULL)Arg->err=1;
	
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

void LPrint(FILE *outputfp,struct PBArg *Arg,int h,double cost,int mode){
	
	
	if (mode==2){
		if (Arg->err==0){
			fprintf(outputfp,"%d %d %s %d %d %.2lf\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj,cost);
		} else fprintf(outputfp,"%d %d %s %d %d -1\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,Arg->vj);
		
	}else if (Arg->err==0){
		fprintf(outputfp ,"%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi,h);
	} else  fprintf(outputfp ,"%d %d %s %d -1\n\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	
	return;
	
}

