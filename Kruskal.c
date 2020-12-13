#include <stdlib.h>
#include "Kruskal.h"
#include "Graph.h"

/***********************************************************************************************************************
 * Initialization of the 2 arrays required for CWQU
 * @param V Size of the arrays
 * @param id root array
 * @param sz size array TODO
 **********************************************************************************************************************/
void UFinit(int V, int *id, int *sz) {
	
	int i;
	
	for (i = 0; i < V; i++) {
		id[i] = i;   /* Initialize every root as their own */
		sz[i] = 1;   /* Initialize every size as 1 */
	}
}

/***********************************************************************************************************************
 * Function to check for finds in CWQU
 * @param p 1st vertice of the found edge
 * @param q 2nd vertice of the found edge
 * @param id root array containing current state of CWQU
 * @return return TODO
 **********************************************************************************************************************/
int UFfind(int p, int q, int *id) {
	int i, j;
	
	for (i = p - 1; i != id[i]; i = id[i]);
	for (j = q - 1; j != id[j]; j = id[j]);
	if (i == j) {
		return 1;
	} else {
		return 0;
	}
}

/***********************************************************************************************************************
 * Function to add a new union to the existing CWQU 
 * @param p 1st Vertice of the found edge
 * @param q 2nd Vertice of the found edge
 * @param id root array containing current state of CWQU
 * @param sz size array of the current state of CWQU
 **********************************************************************************************************************/
void UFunion(int p, int q, int *id, int *sz) {
	int i, j, x, t;
	
	for (i = p - 1; i != id[i]; i = id[i]); /*Find root p*/
	for (j = q - 1; j != id[j]; j = id[j]); /*Find root q*/
	
	if (sz[i] < sz[j]) {
		id[i] = j;
		sz[j] += sz[i];
		t = j;
	} else {
		id[j] = i;
		sz[i] += sz[j];
		t = i;
	}
	for (i = p - 1; i != id[i]; i = x) {
		x = id[i];
		id[i] = t;
	} /*Change root p*/
	for (j = q - 1; j != id[j]; j = x) {
		x = id[j];
		id[j] = t;
	} /*Change root q*/
	
}

/***********************************************************************************************************************
 * Function to return the smaller vertice out of two. Required for qsort
 * @param a 1st Vertice
 * @param b 2nd Vertice
 * @return 0 if 1st if smaller, 1 else 
 **********************************************************************************************************************/
int lessVertice(const void *a, const void *b) {
	
	struct edge *va, *vb;
	
	va = *(struct edge **) a;   /* typedef the 2 items, because sorting criteria for the qsort function can only have */
	vb = *(struct edge **) b;   /* entry parameters as constant void pointers */
	
	if (va->vi < vb->vi) return 0;   /* if 1st is smaller */
	else if (va->vi == vb->vi) { /* if they´re equal*/
		if (va->vj < vb->vj)return 0; /* Check 2nd vertice */
		else return 1;
	} else return 1;   /* if 2nd is smaller */
}

/***********************************************************************************************************************
 * Function to return the smaller cost out of two. Required for qsort
 * @param a 1st cost
 * @param b 2nd cost
 * @return 0 if 1st if smaller, 1 else 
 **********************************************************************************************************************/
int lessCost(const void *a, const void *b) {
	
	struct edge *va, *vb;
	
	va = *(struct edge **) a;   /* typedef the 2 items, because sorting criteria for the qsort function can only have */
	vb = *(struct edge **) b;   /* entry parameters as constant void pointers */
	
	if (va->cost > vb->cost) { /*if 2nd cost is smaller*/
		return 1;
	} else {   /* if 1st cost is smaller or they´re equal */
		return 0;
	}
}

/***********************************************************************************************************************
 * Function to run full Kruskal´s Algorithm
 * @param g Graph
 * @param cost total cost of the minimum support tree
 * @return
 **********************************************************************************************************************/
int Kruskal(struct graph *g, double *cost) {
	int i, j, k;   /* Auxiliary Variables for the cycles */
	int *id = NULL, *sz = NULL, cnt = 0;   /* arrays necessary to the CWQU and Union count */
	struct edge **data;   /* New edge array to store the minimum support tree */
	
	if ((id = (int *) malloc(g->Arg->v * sizeof(int))) == NULL) ErrExit(3);   /* Memory Allocation for CWQU Array */
	if ((sz = (int *) malloc(g->Arg->v * sizeof(int))) == NULL) ErrExit(3);
	data = (struct edge **) malloc(
			g->Arg->e * sizeof(struct edge *));   /* Memory Allocation for the min support tree */
	
	UFinit(g->Arg->v, id, sz);  /* Initialization of the CWQU arrays */
	qsort(g->data, g->Arg->e, sizeof(struct edge *), lessCost);   /* Sort the graph by cost criteria */
	
	for (i = 0, k = 0, j = g->Arg->e - 1; k <= j; i++) {
		
		if (!UFfind(g->data[i]->vi, g->data[i]->vj, id)) { /* When no find is found, add the new union */
			UFunion(g->data[i]->vi, g->data[i]->vj, id, sz);
			data[k++] = g->data[i];   /* Add edge to the minimum support tree */
			
			*cost += g->data[i]->cost;   /* Adding to the sum of cost */
			cnt++;   /* Union count */
		} else {
			data[j] = g->data[i];   /* If the edge isn´t part of the minimum support tree, send it to the "end" */
			j--;
		}
	}
	
	/* Edges that didn´t make it to the mst got placed in the end upside down, so they need reversing */
	Reverse(data, j + 1, g->Arg->e - 1);
	free(g->data);   /* free the old graph representation */
	g->data = data;   /* adding the new representation to the graph */
	
	free(id);   /* CWQU is finished, these arrays are no longer needed */
	free(sz);
	return cnt;   /* Return the number of unions, interpreted as the number of edges in the minimum support tree  */
}

/***********************************************************************************************************************
 * Function to invert all edges in a given array
 * @param data array to reverse
 * @param start 1st position to reverse
 * @param end last position to reverse
 **********************************************************************************************************************/
void Reverse(struct edge **data, int start, int end) {
	int i, j;   /* Auxiliary Variables for the cycle */
	struct edge *temp;   /* temporary edge for the switch */
	
	for (i = start, j = end; i < j; i++, j--) { /* i starts in first and j starts at the end, meeting in the middle */
		
		if (data[i]->cost > data[j]->cost)/* Check if cost is as expected */
		{
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
}

/***********************************************************************************************************************
 * A broken down version of Kruskal´s Algorithm, which can stop and continue CWQU as required
 * @param data Cost Sorted Edge array
 * @param V N
 * @param cost Cost of the minimum support tree
 * @param id root array for CWQU
 * @param sz size array for CWQU
 * @param Stop position to stop the execution of CWQU
 * @return Number of Unions
 **********************************************************************************************************************/
int CWQU(struct edge **data, int V, double *cost, int *id, int *sz, int Stop) {
	
	int i, cnt = 0;
	
	UFinit(V, id, sz);/*TODO*/
	
	for (i = 0; i < Stop; i++) {
		if (data[i]->cost > 0) {   /* Doesn´t use edges that have been marked by SearchDelete */
			if (!UFfind(data[i]->vi, data[i]->vj, id)) {   /* Checking for finds */
				UFunion(data[i]->vi, data[i]->vj, id, sz);   /* If none found, then add the edge to the mst */
				*cost += data[i]->cost;   /* add the cost of the newly added edge to the sum */
				cnt++;
			}
		}
	}
	return cnt;   /* Return the number of unions made */
}

/***********************************************************************************************************************
 * Function to search for gaps in connectivity
 * @param data array to be searched
 * @param id root array of CWQU´s current state
 * @param sz size array of CWQU´s current state
 * @param start position to start search
 * @param end last position to search
 * @return position of the newly added union if one is found, -1 else
 **********************************************************************************************************************/
int binsearch(struct edge **data, int *id, int *sz, int start, int end) {
	
	int i;   /*Auxiliary var*/
	
	for (i = start; i < end; i++) {
		
		if (!UFfind(((struct edge **) data)[i]->vi, ((struct edge **) data)[i]->vj, id)) {
			UFunion(((struct edge **) data)[i]->vi, ((struct edge **) data)[i]->vj, id, sz);
			return i;   /* If one new union is found, immediate return */
		}
	}   /* If multiple gaps are expected, this function can be run in a cycle, finding all the new edges  */
	return -1;
}

/***********************************************************************************************************************
 * Function to search for gaps in connectivity, whilst ignoring edges marked as unusable
 * @param data array to be searched
 * @param id root array of CWQU´s current state
 * @param sz size array of CWQU´s current state
 * @param start position to start search
 * @param end last position to search
 * @return position of the newly added union if one is found, -1 else
 **********************************************************************************************************************/
int N_binsearch(struct edge **data, int *id, int *sz, int start, int end) {
	
	int i;
	
	for (i = start; i < end; i++) {
		if (data[i]->cost > 0) {   /* Edges marked as unusable will have their cost negative */
			if (!UFfind(((struct edge **) data)[i]->vi, ((struct edge **) data)[i]->vj, id)) {
				UFunion(((struct edge **) data)[i]->vi, ((struct edge **) data)[i]->vj, id, sz);
				return i; /* If one new union is found, immediate return */
			}
		}   /* If multiple gaps are expected, this function can be run in a cycle, finding all the new edges  */
	}
	return -1;
}