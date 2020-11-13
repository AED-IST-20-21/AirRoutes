//
// Created by anton on 11/12/2020.
//

#include "List.h"

void LControl (FILE *fp, struct PBArg *Arg){
	
	if ((strcmp(Arg->var,"A0"))==0){
		
		AZero(fp,Arg);
		return;
		
	} else if ((strcmp(Arg->var,"B0"))==0) {
		
		BZero(fp,Arg);
		return;
		
	}else if ((strcmp(Arg->var,"C0"))==0) {
		
		CZero(fp,Arg);
		return;
		
	}else if ((strcmp(Arg->var,"D0"))==0) {
		
		DZero(fp,Arg);
		return;
		
	} else {
		
		ErrExit(2);
		return;
	}
}

/**************************************
 * Function to determine the degree while reading an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
void AZero(FILE *fp,struct PBArg *Arg){
	
	int i=0,j=0,k=0,g=0;
	struct edge *aux;
	
	do{
		
		aux=EdgeRead(fp);
		k++;
		
		if (aux->vi==Arg->vi)
			g++;
		
	}while (k<V)
	
		/* Print g TODO */
	return;
}

/**************************************
 * Function to determine if there is an edge between 2 vertices while reading from an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
 
void BZero(FILE *fp,struct PBArg *Arg){
	
	struct edge *aux;
	float auxcost;
	bool Flag;
	
	do{
	
	aux=EdgeRead(fp);
		
		if ((aux->vi==Arg->vi)&&(aux->vj==Arg->vj)&&(Flag==F)){
			Flag=T;
			auxcost=aux->cost;
			/*Print Edge */
		}
		
	}while (k<V)
	
	/* Print doesn´t exist TODO */
	return;
}

