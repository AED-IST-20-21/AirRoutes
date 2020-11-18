
#include "Zero.h"

#include <stdbool.h>

void LControl (FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
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
}

/**************************************
 * Function to determine the degree while reading an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
void AZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg){
	
	int k=0,g=0;
	struct edge *aux;
	
	if((aux=malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
		
		aux=EdgeRead(entryfp,aux);
		k++;
		
		if ((aux->vi==Arg->vi)&&(aux->vj==Arg->vi))
			g++;
		
	} while (k<Arg->v);
	
	fprintf(outputfp,"%d %d %s %d %d",Arg->v,Arg->e,Arg->var,Arg->vi,g);
	
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
	short int Flag;
	int k=0;
	
	if((aux=malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
	
	aux=EdgeRead(entryfp,aux);
		
		if (((aux->vi==(Arg->vi)||(Arg->vj))&&(aux->vj==(Arg->vj)||(Arg->vj)))&&(Flag==0)){
			
			Flag=1;
			fprintf(outputfp,"%d %d %s %d %f",Arg->v,Arg->e,Arg->var,Arg->vi,aux->cost);
		}
		
	}while (k<Arg->v);
	if (Flag==0)
		fprintf(outputfp,"%d %d %s %d Doesn´t Exist",Arg->v,Arg->e,Arg->var,Arg->vi);
	
	free(aux);
	
	return;
}

void CZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	struct list *aux[2];
	
	G = LGRead(entryfp, Arg);
	
	ListTurn(G->vertice[Arg->vi],ON);
	
	aux[0]=G->vertice[Arg->vi]; /* Lista de todos os adjacentes a vi */
	
	while (aux[0]!=NULL)
	{
		
		aux[1]=G->vertice[aux[0]->v];
		
		if (LampFind(aux[1],CZ)!=0)
		{
			fprintf(outputfp ,"%d %d %s %d 1\n", Arg->v, Arg->e, Arg->var, Arg->vi);
			ListTurn(G->vertice[Arg->vi],OFF);
			return;
		}
		
		aux[0]=aux[0]->next;
	}

	fprintf(outputfp ,"%d %d %s %d 0\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	ListTurn(G->vertice[Arg->vi],OFF);
	return;
}

void DZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	struct list *aux[2];
	int cnt=0;
	
	G = LGRead(entryfp, Arg);
	
	ListTurn(G->vertice[Arg->vi],ON);
	
	aux[0]=G->vertice[Arg->vi]; /* Lista de todos os adjacentes a vi */
	
	while (aux[0]!=NULL)
	{
		aux[1]=G->vertice[aux[0]->v];
		cnt += LampFind(aux[1],CZ);
		aux[0]=aux[0]->next;
	}
	
	fprintf(outputfp ,"%d %d %s %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi,cnt);
	ListTurn(G->vertice[Arg->vi],OFF);
	return;
}

/**
 * Function to turn all the lights on or off
 * @param L List to switch the lights
 * @param mode Switch on or off
 */
int ListTurn(struct list *L,enum mode){

	struct list *aux=L;
	int g=0;
	
	while (aux!=NULL){
		
		aux->lamp=mode;
		aux=aux->next;
		g++;
	}
	return g;
}

/**
 * Function to find On Lamps in a list
 * @param L List
 * @param mode Find 1 lamp or count the number of lamps on
 * @return Lamps found
 */
int LampFind(struct list *L,enum mode,int g){
	
	struct list *aux=L;
	int c=0;
	
	
	
	if (mode==CZ){
			while (aux!=NULL){
		
			if (aux->lamp==ON)
				return 1;
			
			aux=aux->next;
		
		}
		return 0;
	}else {
		
		while (aux!=NULL){
			
			if (aux->lamp==ON)
				c++;
				aux->lamp=Visited;
			
			aux=aux->next;
			
		}
		return c;
		
		
	}
}