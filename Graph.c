//
// Created by anton on 11/30/2020.
//

#include "Graph.h"

struct graph *GraphInit() {
	struct graph *G;
	
	if ((G = (struct graph *) malloc(sizeof(struct graph))) == NULL)
		ErrExit(3);
	
	return G;
}

/**********************
 * Memory allocation and Initialization of PBArg
 * @return clean PBArg
 *********************/

struct PBArg *PBinit() {
	
	struct PBArg *aux;
	
	if ((aux = (struct PBArg *) malloc(sizeof(struct PBArg))) == NULL)
		ErrExit(3);
	
	aux->v = 0;
	aux->e = 0;
	aux->vi = 0;
	aux->vj = 0;
	aux->var[0] = '\0';
	aux->err = 0;
	
	return aux;
}

/********************************
 * Function to check if the problem arguments are valid
 * @param aux Struct containing the problem arguments
 * @return mode if OK -1 else
 */
int ArgCheck(struct PBArg *aux) {
	if ((aux->v > 0) && (aux->e > 0)) {
		
		if (strcmp(aux->var, "A0") == 0) {
			return 1;
			
		} else if (strcmp(aux->var, "B0") == 0) {
			return 2;
			
		} else if (strcmp(aux->var, "C0") == 0) {
			return 3;
			
		} else if (strcmp(aux->var, "D0") == 0) {
			return 4;
			
		} else if (strcmp(aux->var, "A1") == 0) {
			return 11;
			
		} else if (strcmp(aux->var, "B1") == 0) {
			return 12;
			
		} else if (strcmp(aux->var, "C1") == 0) {
			return 13;
			
		} else if (strcmp(aux->var, "D1") == 0) {
			return 14;
			
		} else return -1;
		
	} else {
		return -1;
	}
}

void GFree(struct graph *g) {
	
	if (ArgCheck(g->Arg)<10){
		
		FreeListV(g->data, g->Arg->v);
	
	}else free(g->data);
	
	free(g);
	
	return;
}







