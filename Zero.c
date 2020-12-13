
#include "Zero.h"


#include <stdbool.h>

void LControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	int G = 0, AC;
	double cost = 0;
	
	switch (AC = ArgCheck(Arg)) {
		case 1: {
			G = AZero(entryfp, Arg);
			break;
		}
		case 2: {
			G = BZero(entryfp, Arg, &cost);
			break;
		}
		case 3: {
			G = CZero(entryfp, Arg);
			break;
		}
		case 4: {
			G = DZero(entryfp, Arg);
			break;
			
		}
		default: {
			Arg->err = 1;
			break;
		}
	}
	
	LPrint(outputfp, Arg, G, cost, AC);
	
	free(Arg);
	return;
}

int AZero(FILE *entryfp, struct PBArg *Arg) {
	
	int k = 0, g = 0;
	struct edge *aux;
	
	if ((aux = (struct edge *) malloc(sizeof(struct edge))) == NULL)
		ErrExit(3);
	
	do {
		
		if ((aux = EdgeRead(entryfp, aux)) == NULL) Arg->err = 1;
		if ((EdgeCheck(aux, Arg->v)) < 0) Arg->err = 1;
		
		if ((aux->vi == Arg->vi) || (aux->vj == Arg->vi))
			g++;
		
		k++;
	} while (k < Arg->e);
	
	free(aux);
	
	if (g <= 0) Arg->err = 1;
	
	return g;
}

int BZero(FILE *entryfp, struct PBArg *Arg, double *cost) {
	struct edge *aux;
	short int Flag = 0;
	int k = 0;
	
	if ((aux = (struct edge *) malloc(sizeof(struct edge))) == NULL)
		ErrExit(3);
	
	while (k < Arg->e) {
		
		if ((aux = EdgeRead(entryfp, aux)) == NULL) Arg->err = 1;
		if ((EdgeCheck(aux, Arg->v)) < 0) Arg->err = 1;
		
		if ((((aux->vi == Arg->vi) && (aux->vj == Arg->vj)) || ((aux->vj == Arg->vi) && (aux->vi == Arg->vj))) &&
		    (Flag == 0)) {
			
			Flag = 1;
			*cost = aux->cost;
		}
		k++;
	}
	
	free(aux);
	
	if (Flag == 0) Arg->err = 1;
	
	return (int) Flag;
}

int CZero(FILE *entryfp, struct PBArg *Arg) {
	struct graph0 *G;
	int *lamps, i, lenght, c = 0;
	
	if ((G = LGRead(entryfp, Arg)) == NULL)Arg->err = 1;
	
	if ((Arg->vi > Arg->v) || (Arg->vi <= 0)) {
		
		Arg->err = 1;
		
	} else {
		
		lenght = LenghtList(((struct list **) G->data)[Arg->vi - 1]);
		lamps = LampsInit(((struct list **) G->data)[Arg->vi - 1], lenght);
		
		
		for (i = 0; (c < 1) && (i < lenght); i++) { /*Adaptative*/
			
			c += ClickFind(((struct list **) G->data)[lamps[i] - 1], lamps, lenght, i);
			
		}
		
		free(lamps);
	}
	
	LGFree(G);
	if (c > 0) {
		c = 1;
	}
	
	return c;
}

int DZero(FILE *entryfp, struct PBArg *Arg) {
	struct graph0 *G;
	int *lamps, i, lenght, c = 0;
	
	if ((G = LGRead(entryfp, Arg)) == NULL)Arg->err = 1;
	
	if ((Arg->vi > Arg->v) || (Arg->vi <= 0)) {
		
		Arg->err = 1;
		
	} else {
		
		lenght = LenghtList(((struct list **) G->data)[Arg->vi - 1]);
		lamps = LampsInit(((struct list **) G->data)[Arg->vi - 1], lenght);
		
		
		for (i = 0; (i < lenght); i++) {
			
			c += ClickFind(((struct list **) G->data)[lamps[i] - 1], lamps, lenght, i);
			
		}
		
		free(lamps);
	}
	
	LGFree(G);
	return c;
}




