#include <stdlib.h>

#include "ListGraph.h"



Graph* GraphInit(struct PBArg *Arg)
{
	Graph *G;
	
	if (G = (Graph *) malloc(sizeof(struct graph))==NULL)
		ErrExit(3);
	
	G->Arg = Arg;
	
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