//
// Created by anton on 11/12/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#include "Zero.h"
#include "FileOp.h"
#include "ListGraph.h"

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
		
		if ((aux->vi==(Arg->vi)||(Arg->vj))&&(aux->vj==(Arg->vj)||(Arg->vj)))&&(Flag==0)){
			
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
	struct Graph *G;
	struct edge *click[3];
	
	G=LGRead(entryfp,Arg->v);
	ClickFind()
}

void DZero(FILE *entryfp,FILE *outputfp, struct PBArg *Arg)
{
	return;
}

/**
 * Function to read entire graph from file 
 * @param entryfp File from which to read
 * @param v Number
 * @param Arg 
 * @return 
 */
struct graph *LGRead(FILE *entryfp,struct PBArg *Arg) {
	
	struct graph *G;
	struct edge *temp;
	
	G = GraphInit(Arg);
	
	for (i = 0; i < Arg->v; i++) {
		
		if (fscanf(entryfp, "%d %d %f", temp->vi, temp->vj, temp->cost) != 3)
			ErrExit(5);
		
		AddList(G->vertice, temp);
	}
	
	return G;
}




