/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#include "Zero.h"

/***********************************************************************************************************************
 * Function to control modes that represent the graph as an array of adjacency list
 * @param entryfp File to read from
 * @param outputfp File to write to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void LControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	int G = 0, AC;   /* Auxiliary variables */
	double cost = 0;   /* Cost */
	
	switch (AC = ArgCheck(Arg)) {   /* ArgCheck returns an integer representing the mode */
		case 1: {   /* mode A0 */
			G = AZero(entryfp, Arg);
			break;
		}
		case 2: {   /* mode B0 */
			G = BZero(entryfp, Arg, &cost);
			break;
		}
		case 3: {   /* mode C0 */
			G = CZero(entryfp, Arg);
			break;
		}
		case 4: {   /* mode D0 */
			G = DZero(entryfp, Arg);
			break;
			
		}
		default: {   /* Planned exception */
			Arg->err = 1;
			break;
		}
	}
	
	LPrint(outputfp, Arg, G, cost, AC);   /* Print the graph */
	free(Arg);
}

/***********************************************************************************************************************
 * Function to control mode A0, which outputs the degree of a vertice
 * @param entryfp File to read from
 * @param Arg Problem Argument
 * @return The degree of the vertice
 **********************************************************************************************************************/
int AZero(FILE *entryfp, struct PBArg *Arg) {
	
	int k = 0, g = 0;   /* Auxiliary Variable and degree counter */
	struct edge *aux;   /* Temporary edge */
	
	if ((aux = (struct edge *) malloc(sizeof(struct edge))) == NULL) ErrExit(3);
	
	do {
		/* Read one edge */
		if ((aux = EdgeRead(entryfp, aux)) == NULL) Arg->err = 1;
		if ((EdgeCheck(aux, Arg->v)) < 0) Arg->err = 1;
		/* Check vertices */
		if ((aux->vi == Arg->vi) || (aux->vj == Arg->vi)) g++;
		
		k++;
	} while (k < Arg->e);   /* Only one edge is required */
	
	free(aux);
	
	if (g <= 0) Arg->err = 1;
	
	return g;
}

/***********************************************************************************************************************
 * Function to control mode B0, which checks for connectivity between 2 vertices
 * @param entryfp File to read from
 * @param Arg Problem Arguments
 * @return The 1 if they are connected, 0 if they´re not
 **********************************************************************************************************************/
int BZero(FILE *entryfp, struct PBArg *Arg, double *cost) {
	struct edge *temp=NULL;   /* Temporary edge */
	int Flag = 0,k = 0;   /* Flag to return and Auxiliary Variable for the cycle */
	
	while (k < Arg->e) {   /* Run trough all edges in the graph  */
		
		if ((temp = EdgeRead(entryfp, temp)) == NULL) Arg->err = 1; /* Read one edge */
		if ((EdgeCheck(temp, Arg->v)) < 0) Arg->err = 1;   /* Check if edge is valid */
		
		if ((((temp->vi == Arg->vi) && (temp->vj == Arg->vj)) || ((temp->vj == Arg->vi) && (temp->vi == Arg->vj))) &&
		    (Flag == 0)) {   /* Looks for the argument vertices in the current edge */
			
			Flag = 1;
			*cost = temp->cost;
		}
		k++;
	}
	
	free(temp);
	
	if (Flag == 0) Arg->err = 1;
	
	return Flag;
}

/***********************************************************************************************************************
 * Function to control mode C0, which looks for 1 click (cycle between 3 vertices) in one vertice
 * @param entryfp File to read from
 * @param Arg Problem Arguments
 * @return The 1 if click is found, 0 otherwise
 **********************************************************************************************************************/
int CZero(FILE *entryfp, struct PBArg *Arg) {
	struct graph0 *G;   /* Graph represented as an array of adjacency lists */
	int *lamps, i, lenght, c = 0;   /* Auxiliary Variables */
	
	if ((G = LGRead(entryfp, Arg)) == NULL)Arg->err = 1;   /* Read the Graph */
	
	if ((Arg->vi > Arg->v) || (Arg->vi <= 0)) {
		
		Arg->err = 1;   /* Vertice outside the graph */
		
	} else {
		
		lenght = LenghtList(((struct list **) G->data)[Arg->vi - 1]);   /* Get the lenght of the list */
		lamps = LampsInit(((struct list **) G->data)[Arg->vi - 1], lenght);   /* Inicialize arrays needed for search */
		
		
		for (i = 0; (c < 1) && (i < lenght); i++) { /* Run all vertices until a click is found  */
			
			c += ClickFind(((struct list **) G->data)[lamps[i] - 1], lamps, lenght, i);
			
		}
		
		free(lamps);
	}
	
	LGFree(G);
	if (c > 0) {   /* For Printing porpuses, in this mode we only want 1 click */
		c = 1;
	}
	
	return c;
}

/***********************************************************************************************************************
 * Function to control mode D0, which looks for clicks (cycles between 3 vertices)
 * @param entryfp File to read from
 * @param Arg Problem Arguments
 * @return Number of clicks found
 **********************************************************************************************************************/
int DZero(FILE *entryfp, struct PBArg *Arg) {
	struct graph0 *G;   /* Graph represented as an array of adjacency lists */
	int *lamps, i, lenght, c = 0;   /* Auxiliary Variables */
	
	if ((G = LGRead(entryfp, Arg)) == NULL)Arg->err = 1;   /* Read the graph */
	
	if ((Arg->vi > Arg->v) || (Arg->vi <= 0)) {   /* Vertice to check outside the graph */
		
		Arg->err = 1;
		
	} else {
		
		lenght = LenghtList(((struct list **) G->data)[Arg->vi - 1]);   /* Get the lenght of the list */
		lamps = LampsInit(((struct list **) G->data)[Arg->vi - 1], lenght);   /* Inicialize arrays needed for search */
		
		
		for (i = 0;(i < lenght); i++) { /* Run all vertices and count the clicks found */
			
			c += ClickFind(((struct list **) G->data)[lamps[i] - 1], lamps, lenght, i);
			
		}
		
		free(lamps);
	}
	
	
	LGFree(G);
	return c;
}