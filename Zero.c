
#include "Zero.h"

#include <stdbool.h>

void LControl (FILE *entryfp, FILE *outputfp, struct PBArg *Arg)
{

	switch(ArgCheck(Arg))
	{
		case 1:
		{
			AZero(entryfp,outputfp,Arg);
			break;
		}
		case 2:
		{
			BZero(entryfp,outputfp,Arg);
			break;
		}
		case 3:
		{
			CZero(entryfp,outputfp,Arg);
			break;
		}
		case 4:
		{
			DZero(entryfp,outputfp,Arg);
			break;
		
		}
		default:
		{
		
			ErrExit(2);
			return;
		}
	}
	free(Arg);
	return;
}

/**************************************
 * Function to determine the degree while reading an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
void AZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg){
	
	int k=0,g=0;
	struct edge *aux;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
		
		aux = EdgeRead(entryfp,aux);
		k++;
		
		if ((aux->vi==Arg->vi)||(aux->vj==Arg->vi))
			g++;
		
	} while (k < Arg->e);

	/*printf("%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, g);*/
	fprintf(outputfp,"%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, g);
	
	free(aux);

	return;
}

/**************************************
 * Function to determine if there is an edge between 2 vertices while reading from an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
 
void BZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct edge *aux;
	short int Flag=0;
	int k=0;
	
	if((aux = (struct edge*) malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	while (k<Arg->e){
	
		aux=EdgeRead(entryfp,aux);
		
		if (( (aux->vi==((Arg->vi)||(Arg->vj))) || (aux->vj==((Arg->vi)||(Arg->vj)))) && (Flag==0) ){
			
			Flag=1;
			/*printf("%d %d %s %d %.2f\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,aux->cost);*/
			fprintf(outputfp,"%d %d %s %d %.2f\n\n",Arg->v,Arg->e,Arg->var,Arg->vi,aux->cost);
		}
		
		k++;
		
	}
	
	
	
	if (Flag==0){
		/*printf("%d %d %s %d doesn't exist\n\n",Arg->v,Arg->e,Arg->var,Arg->vi);*/
		fprintf(outputfp,"%d %d %s %d doesn't exist\n\n",Arg->v,Arg->e,Arg->var,Arg->vi);
	}
	free(aux);
	
	return;
}

void CZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;

	G = LGRead(entryfp, Arg);
	
	lamps=LampsInit(G->vertice[Arg->vi-1]);
	lenght=LenghtList(G->vertice[Arg->vi-1]);
	
	for (i=0;(c==0)&&(i<lenght);i++){
		
		c+=ClickFind(G->vertice[lamps[i]-1],lamps,lenght,i);
		
	}
	if (c==0){
		fprintf(outputfp ,"%d %d %s %d 0\n\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	} else if (c>0){
		fprintf(outputfp ,"%d %d %s %d 1\n\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	} else {
		ErrExit(1);
	}
	
	free(lamps);
	LGFree(G);
	
	return;
}

void DZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	int *lamps,i,lenght,c=0;
	
	G = LGRead(entryfp, Arg);
	
	lamps=LampsInit(G->vertice[Arg->vi-1]);
	lenght=LenghtList(G->vertice[Arg->vi-1]);
	
	for (i=0;(c==0)&&(i<lenght);i++){
		
		c+=ClickFind(G->vertice[lamps[i]-1],lamps,lenght,i);
		
	}
	if (c==0){
		fprintf(outputfp ,"%d %d %s %d 0\n\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	} else if (c>0){
		fprintf(outputfp ,"%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi,c);
	} else {
		ErrExit(1);
	}
	free(lamps);
	LGFree(G);
	return;
}

int *LampsInit(struct list *lvi){
	
	int *lamps,lenght=LenghtList(lvi),i;
	struct list *laux;
	
	if ((lamps = (int *) calloc(lenght,sizeof(int))) == NULL)
		ErrExit(3);
	
	laux=lvi;
	
	for (i=0;i<lenght;i++){
		
		Sort(lamps,laux->v,lenght);
		
		laux=laux->next;
	}
	return lamps;
}

void Sort(int *a,int v, int size)
{
	int i,temp;
	
	for (i=0;i<size-1;i++){

		a[0]=v;
		if (a[i+1]<a[i]){
			
			temp=a[i+1];
			a[i+1]=a[i];
			a[i]=temp;
		}
		
	}
	
	return;
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