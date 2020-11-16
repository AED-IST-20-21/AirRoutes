//
// Created by anton on 11/12/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#include "List.h"
#include "FileOp.h"
#include "Graph.h"

void LControl (FILE *fp, struct PBArg *Arg)
{
	switch(ArgCheck(Arg))
	{
		case 1:
		{
			AZero(fp,Arg);
			break;
		}
		case 2:
		{
			BZero(fp, Arg);
			break;
		}
		case 3:
		{
			CZero(fp, Arg);
			break;
		}
		case 4:
		{
			DZero(fp,Arg);
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
void AZero(FILE *fp, struct PBArg *Arg){
	
	int i=0,j=0,k=0,g=0, V=0;
	struct edge *aux;
	
	if((aux=malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
		
		aux=EdgeRead(fp,aux);
		k++;
		
		if (aux->vi==Arg->vi)
			g++;
		
	} while (k<V);
	
		/* Print g TODO */
	return;
}

/**************************************
 * Function to determine if there is an edge between 2 vertices while reading from an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
 
void BZero(FILE *fp, struct PBArg *Arg)
{
	struct edge *aux;
	float auxcost;
	bool Flag, T, F;
	int k, V;
	
	if((aux=malloc(sizeof(struct edge)))==NULL)
		ErrExit(3);
	
	do{
	
	aux=EdgeRead(fp,aux);
		
		if ((aux->vi==Arg->vi)&&(aux->vj==Arg->vj)&&(Flag==F)){
			Flag=T;
			
			/*Print Edge using aux */
		}
		
	}while (k<V);
	
	free(aux);
	
	/* Print doesn't exist TODO */
	return;
}

void CZero(FILE *fp, struct PBArg *Arg)
{
	return;
}

void DZero(FILE *fp, struct PBArg *Arg)
{
	return;
}


