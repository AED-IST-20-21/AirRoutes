/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#include "Graph.h"

/***********************************************************************************************************************
 * Function to handle unplanned Errors
 * @param err Error type
 **********************************************************************************************************************/
void ErrExit(int err) {
	
	switch (err) {
		case 0:
#ifdef DEBUG
			fprintf(stderr, "Error Opening File\n");
#endif
			exit(0);
		
		case 1:
#ifdef DEBUG
			fprintf(stderr, "Error Checking File Extension\n");
#endif
			exit(0);
		
		case 2:
#ifdef DEBUG
			fprintf(stderr, "Invalid Mode\n");
#endif
			exit(0);
		
		case 3:
#ifdef DEBUG
			fprintf(stderr, "Error Allocating Memory\n");
#endif
			exit(0);
		
		case 4:
#ifdef DEBUG
			fprintf(stderr, "Invalid Arguments\n");
#endif
			exit(0);
		
		case 5:
#ifdef DEBUG
			fprintf(stderr, "Error Reading Graph\n");
#endif
			exit(0);
		
		case 6:
#ifdef DEBUG
			fprintf(stderr, "Error Reading Edge\n");
#endif
			exit(0);
		
	}
	return;
}

/***********************************************************************************************************************
 * Memory allocation and Initialization of PBArg
 * @return clean PBArg
 **********************************************************************************************************************/
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

/***********************************************************************************************************************
 * Function to allocate memory for a graph
 * @return new graph
 **********************************************************************************************************************/
struct graph *GraphInit() {
	struct graph *G;
	
	if ((G = (struct graph *) malloc(sizeof(struct graph))) == NULL)
		ErrExit(3);
	
	return G;
}

/***********************************************************************************************************************
 * Function to check if the problem arguments are valid
 * @param aux Struct containing the problem arguments
 * @return mode if OK -1 else
 **********************************************************************************************************************/
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
			
		} else if (strcmp(aux->var, "E1") == 0) {
			return 15;
			
		} else return -1;
	} else {
		return -1;
	}
}



