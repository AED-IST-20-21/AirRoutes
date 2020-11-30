//
// Created by anton on 11/30/2020.
//

#include "Graph.h"
struct graph* GraphInit(){
	struct graph *G;
	
	if ((G = (struct graph *) malloc(sizeof(struct graph)))==NULL)
		ErrExit(3);
	
	return G;
}

/**********************
 * Memory allocation and Initialization of PBArg
 * @return clean PBArg
 *********************/
 
struct PBArg *PBinit(){
	
	struct PBArg *aux;
	
	if ((aux = (struct PBArg* ) malloc(sizeof(struct PBArg)))==NULL)
		ErrExit(3);
	
	aux->v = 0;
	aux->e = 0;
	aux->vi = 0;
	aux->vj = 0;
	aux->var[0] = '\0';
	aux->err =0;
	
	return aux;
}

/********************************
 * Function to check if the problem arguments are valid
 * @param aux Struct containing the problem arguments
 * @return mode if OK -1 else
 */
int ArgCheck (struct PBArg *aux){
	if ((aux->v>0)&&(aux->e>0)) {
		
		switch (aux->var) {
			case "A0":
				return 1;
			case "B0":
				return 2;
			case "C0":
				return 3;
			case "D0":
				return 4;
			case "A1":
				return 11;
			case "B1":
				return 12;
			case "C1":
				return 13;
			case "D1":
				return 14;
			default:
				return -1;
		}
	}else return -1;
}





