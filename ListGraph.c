#include <stdlib.h>

#include "ListGraph.h"



struct graph* GraphInit(struct PBArg *Arg){
	Graph *G;
	
	if (G = (struct graph *) malloc(sizeof(struct graph))==NULL)
		ErrExit(3);
	
	G->Arg = Arg;
	
	return G;
}

/**
 * Function to read entire graph from file
 * @param entryfp File from which to read
 * @param v Number
 * @param Arg
 * @return
 */
struct graph *LGRead(FILE *entryfp,struct PBArg *Arg) {
	
	struct graph *G;
	struct edge *temp;
	
	G = GraphInit(Arg);
	G=CreateListV(Arg->v);
	
	for (i = 0; i < Arg->v; i++) {
		
		if (fscanf(entryfp, "%d %d %f", temp->vi, temp->vj, temp->cost) != 3)
			ErrExit(5);
		
		AddList(G->vertice[temp->vi],temp);
		PutList(G->vertice[temp->vi],temp);
		
		
	}
	
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
		
		FreeList(LV[i])
		
	}
	
	free(LV);
	return;
}

/**
 * Function to free a dinamically allocated adjancency list
 * @param L List to be freed
 */
void FreeList(struct list* L){
	struct list *aux, *Prev;
	aux = L;
	while (aux->next != NULL)
	{
		Prev = aux;
		aux = aux->next;
		free(Prev);
	}
	free(aux);
	return;
}

/**
 * Function to allocated memory for a new element
 * @return the space for the new element
 */
struct list* CreateListNode(){
	
	struct list *new;
	
	if(new=(struct list *) malloc(sizeof(list)))==NULL)
		ErrExit(3);

	new->cost=0;
	new->v=0;
	new->next=NULL;
	
	return new;
}

/**
 * Adds a new element to the tail of the list
 * @param L List
 */
void AddList(struct list* L){
	
	L->next = (struct list *) CreateListNode();
	L=L->next;

	return;
}

void PutList(struct list *L,struct edge *new){
	
	L->v=new->vj;
	L->cost=new->cost;
	
	return;
}

/**
 * Allocates memory for a vector of adjacency lists
 * @param V
 * @return
 */
struct list** CreateListV(int V){
	struct list** LV = (struct list**) malloc(V * sizeof(struct list*));
	
	for (i=0;i<V;i++){
		
		LV[i]=CreateListNode();
		
	}
	
	return LV;
}