
#include "Zero.h"


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
	/*struct edge *click[3];*/
	struct list *aux[3];

	int TestMe;
	
	G = LGRead(entryfp, Arg);
	
	aux[0]=G->vertice[Arg->vi]; /* Lista de todos os adjacentes a vi */


	
	while (aux[0]!=NULL)
	{
		aux[1] = G->vertice[ aux[0]->v ];

		if (ClickFind(aux[1],aux[0])!=0)
		{
			fprintf(outputfp ,"%d %d %s %d 1\n", Arg->v, Arg->e, Arg->var, Arg->vi);
			return;
		} 

		aux[0]=aux[0]->next;
	}

	fprintf(outputfp ,"%d %d %s %d 0\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	return;
}

void DZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	struct graph *G;
	struct list* aux[2];

	G = LGRead(entryfp, Arg);

	aux[0]=G->vertice[Arg->vi];

	aux[1]=G->vertice[Arg->vi];
	
	while ( (aux[0]!=NULL) || (ClickFind(aux[1],aux[0])!=0) ){
		
		aux[1]=G->vertice[0]; /*TODO*/
		aux[0]=aux[0]->next;
		/*Avançar I*/
	}

	return;
}

int FindList(struct list *L, int vi){ /* Procura o vértice vi na lista J */
	
	struct list* aux = L;

	while (aux!=NULL)
	{
		if (aux->v == vi)
		{
			return 1;
		}
		aux = aux->next;
	}
	
	return 0;	
}

int ClickFind(struct list* List1, struct list* List2)
{
	int vi, vj;
	struct list *i, *j;

	i=List1;
	j=List2;
	
	while (j!=NULL)
	{

		if (FindList(i, j->v)==1)
		{
			return 1;
		}

		j=j->next;

	}
	return 0;
}

