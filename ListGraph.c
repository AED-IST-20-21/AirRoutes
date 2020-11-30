#include <stdlib.h>

#include "ListGraph.h"
#include "Graph.h"

/**
 * Function to read entire graph from file
 * @param entryfp File from which to read
 * @param v Number
 * @param Arg
 * @return
 */
struct graph *LGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge *temp = NULL;

	int i;
	
	G = GraphInit();

	G->Arg = Arg;

	G->data = (struct list **) CreateListV(Arg->v);

	if ((temp = (struct edge*) malloc(sizeof(struct edge))) == NULL)
		ErrExit(3);
	
	temp->vi = 0;
	temp->vj = 0;
	temp->cost = 0;

	for (i = 0; i < Arg->e; i++) {
		
		if (fscanf(entryfp, "%d %d %lf", &temp->vi, &temp->vj, &temp->cost) != 3){
			LGFree(G);
			return NULL;
		}
		
		G->vertice[temp->vi-1]=AddList(G->vertice[temp->vi-1]);
		PutList(G->vertice[temp->vi-1], temp->vj, temp->cost);
		
		G->vertice[temp->vj-1]=AddList(G->vertice[temp->vj-1]);
		PutList(G->vertice[temp->vj-1], temp->vi, temp->cost);
	
	}
	free(temp);	
	return G;
}

/**
 * Function to free a dinamically allocated vector of adjancency lists
 * @param LV Vector of adjancecncy lists
 * @param V Number of vertices
 */
void FreeListV(struct list **LV,int V){
	
	int i;
	
	for (i=0;i<V;i++){
		
		FreeList(LV[i]);
		
	}
	
	free(LV);
	return;
}

void LGFree(struct graph *g){
	
	FreeListV(g->data,g->Arg->v);
	free(g);
	
	return;
}

/**
 * Function to free a dinamically allocated adjancency list
 * @param L List to be freed
 */
void FreeList(struct list* L){
	struct list *aux, *Prev;
	aux = L;
	while (aux != NULL)
	{
		Prev = aux;
		aux = aux->next;
		free(Prev);
	}
	free(aux);
	return;
}

/**
 * Adds a new element to the tail of the list
 * @param L List
 */
struct list * AddList(struct list* next){
	
	struct list * new;

    /* Memory allocation */
	if ((new = (struct list *) malloc(sizeof(struct list)))==NULL)
        ErrExit(3);

    /* Initialize new node */
    new->v = 0;
	new->cost = 0;
    new->next = next;

    return new;
}

void PutList(struct list *L, int V, double cost){
	
	L->v = V;
	L->cost = cost;
	
	return;
}

/**
 * Allocates memory for a vector of adjacency lists
 * @param V
 * @return
 */
struct list** CreateListV(int V){
	int i;

	struct list** LV = (struct list**) malloc(V * sizeof(struct list*));	
	
	for (i=0; i<V; i++)
	{
		LV[i]=NULL;
	}
	return LV;
}

int LenghtList(struct list *L){
	
	struct list *aux;
	int c=0;
	
	aux=L;
	
	while (aux!=NULL){
	
	c++;
	aux=aux->next;
	
	}
	
	return c;
	
}

int *LampsInit(struct list *lvi,int lenght){
	
	int *lamps,i;
	struct list *laux;
	
	if ((lamps = (int *) calloc(lenght,sizeof(int))) == NULL)
		ErrExit(3);
	
	laux=lvi;
	
	for (i=0;i<lenght;i++){
		
		lamps[i]=laux->v;
		
		laux=laux->next;
	}
	return lamps;
}

int ClickFind(struct list *adj,int *lamps,int size,int j){
	
	int c=0,i;
	struct list *aux;
	
	aux=adj;
	
	while(aux!=NULL){
		for (i=j;i<size;i++){
			if (aux->v==lamps[i]){
				
				c++;
				
			}
		}
		aux=aux->next;
	}
	
	return c;
	
}