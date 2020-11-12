//
// Created by anton on 11/12/2020.
//

#include "List.h"

void LControl (FILE *fp, struct PBArg *Arg){

	int mode=ModeFetch(Arg);
	
	switch (mode){
		case 0:
			AZero(fp,Arg);
			break;
		case 1:
			BZero(fp,Arg);
			break;
		case 2:
			CZero(fp);
			break;
		case 3:
			DZero(fp);
			break;
	}
	
	return;
	
}

/**************************************
 * Function to determine the degree while reading an edge vector
 * @param fp File Pointer
 * @param Arg Problem Arguments
 */
void AZero(FILE *fp,struct PBArg *Arg){
	
	int i=0,j=0,k=0,g=0;
	
	do{
		
		fscanf("%d %d %f",&i,&j) /* Posso dizer o formato e não guardar? question*/
		k++;
		
		if (i==Arg->Vi)
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
	
	bool Flag=F;
	do{
		/* São precisas verificações de fscanf? Quais question*/
		fscanf("%d %d %f",&i,&j) /* Posso dizer o formato do float e não guardar? question*/
		k++;
		
		if (i!=Arg->Vi)&&(j!=Arg->Vj){
		/* Print Edge TODO */
			return;
		}
		
	}while (k<V)
	
	/* Print doesn´t exist TODO */
	return;
}

/*******************************
 * Function to fetch the mode as an integer from the string in the arguments
 * @param Arg Problem Arguments
 * @return Mode
 */
 
int ModeFetch(struct PBArg Arg){
	
	if ((strcmp(Arg.Var,"A0"))==0){
		
		return 0;
		
	} else if ((strcmp(Arg.Var,"B0"))==0) {
		
		return 1;
		
	}else if ((strcmp(Arg.Var,"C0"))==0) {
		
		return 2;
		
	}else if ((strcmp(Arg.Var,"D0"))==0) {
		
		return 3;
		
	} else {
		
		ErrExit(2);
		return -1;
		
	}
}