#include <stdlib.h>

#include "ListGraph.h"

/***********************************************************************************************************************
 *Function to free a graph represented by an adjacency list array
 * @param g Graph to be freed
 **********************************************************************************************************************/
void LGFree(struct graph0 *g) {
	
	FreeListV(g->data, g->Arg->v); /* Free the Adjacency list array */
	free(g);   /* Free Graph pointers */
}

/***********************************************************************************************************************
 * Function to allocate memory for a graph represented by an adjacency list array
 * @return the new graph
 **********************************************************************************************************************/
struct graph0 *Graph0Init() {
	struct graph0 *G;
	
	if ((G = (struct graph0 *) malloc(sizeof(struct graph0))) == NULL) ErrExit(3);
	
	return G;
}

/***********************************************************************************************************************
 * Function to read a graph and store it as an adjacency list array
 * @param entryfp File to read from
 * @param Arg Problem Arguments, which have already been read
 * @return the new complete graph
 **********************************************************************************************************************/
struct graph0 *LGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph0 *G;   /* New Graph */
	struct edge *temp = NULL;   /* Temp edge to overcome fscanf trouble */
	int i;   /* Auxiliary variable for cycle */
	
	G = Graph0Init();   /* Initialize the graph */
	
	G->Arg = Arg;   /* Attaching the problem arguments to the graph */
	
	G->data = CreateListV(Arg->v);   /* Allocate memory for the adjacency list array */
	
	if ((temp = (struct edge *) malloc(sizeof(struct edge))) == NULL)ErrExit(3);   /* Allocate temporary edge */
	
	temp->vi = 0;   /* Initialization of the temporary edge */
	temp->vj = 0;
	temp->cost = 0;
	
	for (i = 0; i < Arg->e; i++) {  /* Read through all the edges on the graph */
		
		if (EdgeRead(entryfp, temp) == NULL) {
			LGFree(G);   /* If there are errors whilst reading, free the graph and return nothing */
			return NULL;
		}
		/* Adding edge to the 1st vertice´s adjacency list  */
		((struct list **) G->data)[temp->vi - 1] = AddList(((struct list **) G->data)[temp->vi - 1]);
		PutList(((struct list **) G->data)[temp->vi - 1], temp->vj, temp->cost);
		/* Adding edge to the 2nd vertice´s adjacency list */
		((struct list **) G->data)[temp->vj - 1] = AddList(((struct list **) G->data)[temp->vj - 1]);
		PutList(((struct list **) G->data)[temp->vj - 1], temp->vi, temp->cost);
		
	}
	free(temp);   /* Free the temporary edge */
	return G;   /* return the new graph with the correct information */
}

/***********************************************************************************************************************
 * Function to free a dynamically allocated array of adjacency lists
 * @param LV Vector of adjacency lists
 * @param V Number of vertices
 **********************************************************************************************************************/
void FreeListV(struct list **LV, int V) {
	
	int i;
	
	for (i = 0; i < V; i++) FreeList(LV[i]);   /* Free all the lists */
	free(LV);   /* Free the array of pointers */
	
}

/***********************************************************************************************************************
 * Function to free a dinamically allocated adjancency list
 * @param L List to be freed
 **********************************************************************************************************************/
void FreeList(struct list *L) {
	
	struct list *aux, *prev;   /* Auxiliary variables to run the list */
	aux = L;   /* Keep the entry parameter pointing to 1st element */
	
	while (aux != NULL) {   /* Keep the pointer to the next and free the current element */
		prev = aux;
		aux = aux->next;
		free(prev);
	}
	free(aux);  /* Free the last pointer */
	return;
}

/***********************************************************************************************************************
 * Adds a new element to the tail of the list
 * @param L List
 **********************************************************************************************************************/
struct list *AddList(struct list *next) {
	
	struct list *new;
	
	/* Memory allocation */
	if ((new = (struct list *) malloc(sizeof(struct list))) == NULL)
		ErrExit(3);
	
	/* Initialize new node */
	new->v = 0;
	new->cost = 0;
	new->next = next;
	
	return new;
}

/***********************************************************************************************************************
 * Adds an element to an adjacency list
 * @param L List to add
 * @param V Element to add
 * @param cost Cost of the edge
 **********************************************************************************************************************/
void PutList(struct list *L, int V, double cost) {
	
	L->v = V;
	L->cost = cost;
}

/***********************************************************************************************************************
 * Allocates memory for a vector of adjacency lists
 * @param V Number of vertices in the array
 * @return the array of adjacency lists
 **********************************************************************************************************************/
struct list **CreateListV(int V) {
	int i;
	
	struct list **LV = (struct list **) malloc(V * sizeof(struct list *));   /* Memory Allocation */
	
	for (i = 0; i < V; i++) {   /* Pointers´ Initialization */
		LV[i] = NULL;
	}
	return LV;   /* Return the array */
}

/***********************************************************************************************************************
 * Function that returns the length of a list
 * @param L List to examine
 * @return Number of elements
 **********************************************************************************************************************/
int LenghtList(struct list *L) {
	
	struct list *aux = L; /* Auxiliary list to not lose Head pointer */
	int c = 0;   /* Count */
	
	while (aux != NULL) {   /* Go through all the elements in the list */
		
		c++;
		aux = aux->next;
	}
	return c;
}

/***********************************************************************************************************************
 * Function to initialize all "lamps" required for the search by ClickFind
 * @param lvi
 * @param lenght
 * @return
 **********************************************************************************************************************/
int *LampsInit(struct list *lvi, int lenght) {
	
	int *lamps, i;   /* lamps array to initialize and auxiliary variable for the cycle */
	struct list *laux = lvi;   /* Auxiliary pointer to the list, to keep track of the head */
	
	if ((lamps = (int *) calloc(lenght, sizeof(int))) == NULL) ErrExit(3);   /* Allocate memory for the array */
	
	for (i = 0; i < lenght; i++) {   /* Run every element of the list */
		
		lamps[i] = laux->v;
		laux = laux->next;
	}
	return lamps;
}

/***********************************************************************************************************************
 * Function to find clicks (cycles of 3 vertices)
 * @param adj Adjacency list to search
 * @param lamps Array containing information if the vertice was previously visited
 * @param size Size of the lamps array
 * @param j TODO
 * @return Click Count
 **********************************************************************************************************************/
int ClickFind(struct list *adj, int *lamps, int size, int j) {
	
	int c = 0, i;   /* Auxiliary variable for the cycle and Click counter */
	struct list *aux = adj;   /* Auxiliary variable to keep track of the list head */

	while (aux != NULL) {
		for (i = j; i < size; i++) {
			if (aux->v == lamps[i]) c++;
		}
		aux = aux->next;
	}
	
	return c;
}
