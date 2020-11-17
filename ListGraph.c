#include <stdlib.h>

#include "ListGraph.h"



struct graph* GraphInit(struct PBArg *Arg)
{
	Graph *G;
	
	if (G = (Graph *) malloc(sizeof(struct graph))==NULL)
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
	
	for (i = 0; i < Arg->v; i++) {
		
		if (fscanf(entryfp, "%d %d %f", temp->vi, temp->vj, temp->cost) != 3)
			ErrExit(5);
		
		AddList(G->vertice, temp);
	}
	
	return G;
}

/**
 * Function to add new edge into vector of adjancency list
 * @param vertice Vector containing the lists of adjancency
 * @param new edge to add
 */
void AddList(struct list *vertice,struct edge *new){
	
	vertice->v=new->vj;
	vertice->cost=new->cost;
	vertice->next=NewListElement();

	return;
}

/**
 * Function to allocate memory for a new adjancency element
 * @return Pointer to new element
 */
struct list *NewListElement(){
	
	struct list *aux;
	
	if(aux=(struct list *) malloc(sizeof(list)))==NULL)
			ErrExit(3);
	return aux;
	
}