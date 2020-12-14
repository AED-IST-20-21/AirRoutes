#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"
#include "VectorGraph.h"
#include "Kruskal.h"

/***********************************************************************************************************************
 * Function to read a graph from the entry file and store it as an edge array
 * @param entryfp File to read from
 * @param Arg Problem Arguments
 * @return Graph with
 **********************************************************************************************************************/
struct graph *VGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph *G = GraphInit();   /* Initialization of the graph */
	int i;   /* Auxiliary Variable for the cycle */
	
	G->Arg = Arg;   /* Connecting the Arguments to the graph */
	G->data = CreateEdgeV(Arg->e);   /* Allocate edge array */
	
	for (i = 0; i < Arg->e; i++) {
		/* Allocate memory for the new edge */
		if ((G->data[i] = (struct edge*) malloc(sizeof(struct edge)))==NULL) ErrExit(3);
		/*Checking for errors during reading*/
		if (fscanf(entryfp, "%d %d %lf", &G->data[i]->vi, &G->data[i]->vj, &G->data[i]->cost) != 3){
			VGFree(G);   /* Planned Exception */
			Arg->err = 1;
			return NULL;
		} else if (EdgeCheck(G->data[i],Arg->v)<0){
			VGFree(G);   /* Planned Exception */
			Arg->err = 1;
			return NULL;
		}
		Format(G->data[i]);   /* Switch vertices if in the wrong order */
	}
	return G;
}

/***********************************************************************************************************************
 * Function to create an Edge Array
 * @param size Size of the edge array
 * @return Clean Edge Array
 **********************************************************************************************************************/
struct edge **CreateEdgeV(int size) {
	
	struct edge **aux;
	
	if ((aux = (struct edge **) malloc(size*sizeof(struct edge *))) == NULL) ErrExit(3);
	
	return aux;
}

/***********************************************************************************************************************
 * Function to search and mark edges as unusable
 * @param g Graph
 * @param start position to start checking
 * @param end position to end checking
 * @param Delete Function Parameter to check for edges to be marked
 * @return Number of edges that were marked
 **********************************************************************************************************************/
int SearchDelete(struct graph *g, int start, int end, int (*Delete)(struct edge *, int, int)) {
	int i, cnt = 0;   /* Auxiliary Variables */
	
	for (i = start; i < end; i++) {   /* Go trough all edges in designated interval */
		
		if ((*Delete)(g->data[i], g->Arg->vi, g->Arg->vj)) {
			
			g->data[i]->cost = -g->data[i]->cost;
			cnt++;
		}
	}
	return cnt;   /* return number of marked edges */
}

/***********************************************************************************************************************
 * Function to check when an edge should be deleted
 * @param aux Edge to be checked
 * @param vi 1st Vertice
 * @param vj 2nd Vertice
 * @return 0 if 1st, 1 if 2nd
 **********************************************************************************************************************/
int EdgeDelete(struct edge *aux, int vi, int vj) {
	
	if (((aux->vi == vi) && (aux->vj == vj)) || ((aux->vj == vi) && (aux->vi == vj))) return 1;
	else return 0;
	
}

/***********************************************************************************************************************
 * Function to check when a vertice should be deleted
 * @param aux Edge to be checked
 * @param vi 1st Vertice
 * @param vj 2nd Vertice
 * @return 1 if OK to delete
 **********************************************************************************************************************/
int VerticeDelete(struct edge *aux, int vi, int vj) {
	
	if ((aux->vi == vi) || (aux->vj == vi)) return 1;
	else return 0;
	
}

/***********************************************************************************************************************
 * Function to free an edge array represented graph
 * @param g Graph to be freed
 **********************************************************************************************************************/
void VGFree(struct graph *g){
	
	FreeEdgeV(g->data,g->Arg->e);
	free(g);
	
}

/***********************************************************************************************************************
 * Function to free an edge array
 * @param data Edge array to be freed
 * @param size Size of said edge array
 **********************************************************************************************************************/
void FreeEdgeV(struct edge **data, int size)
{
	int i;
	
	for (i=0; i<size; i++)
	{
		free(data[i]);
	}
	free(data);
	return;
	
}

/***********************************************************************************************************************
 * Function to Create a copy of an existing graph. Uses only pointers, doesn´t allocate more edges
 * @param source Graph to be copied
 * @return Copy of said graph
 **********************************************************************************************************************/
struct graph *graphcpy(struct graph *source){
	struct graph *new;
	int i;
	new=GraphInit();
	new->Arg=source->Arg;
	new->data=CreateEdgeV(source->Arg->e);
	for (i=0; i < source->Arg->e; i++) new->data[i]=source->data[i];
	return new;
}

/***********************************************************************************************************************
 * Function to solve CWQU of E1 mode TODO
 * @param g Graph to solve
 * @param Sum Original Sum
 * @param StopMe Original Kruskal´s last edge position
 * @return edge array containing all backup edges
 **********************************************************************************************************************/
struct edge* ProblemSolver(struct graph* g, double* Sum, int StopMe)
{
	struct edge* backup;
	int NewStop, ncpos, *id, *sz;
	
	if ((id=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);
	
	NewStop = CWQU(g->data, g->Arg->v, Sum, id, sz, StopMe);
	
	if (StopMe - NewStop > 1)
	{
		free(id);
		free(sz);
		return NULL;
	}
	
	ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);
	
	if (ncpos ==-1)
	{
		free(id);
		free(sz);
		return NULL;
	}
	
	if ((backup = (struct edge*) malloc(sizeof(struct edge)))==NULL) ErrExit(3);
	
	backup->vi = g->data[ncpos]->vi;
	backup->vj = g->data[ncpos]->vj;
	backup->cost = g->data[ncpos]->cost;
	
	free(id);
	free(sz);
	return backup;
}

/***********************************************************************************************************************
 * Function to sort vertices when reading them
 * @param data Edge containing unsorted vertices
 **********************************************************************************************************************/
void Format(struct edge* data)
{
	int temp;

	if (data->vi > data->vj )   /*  if the 1st vertice is larger than the 2nd switch */
	{
		temp = data->vi;
		data->vi = data->vj;
		data->vj = temp;
	}
}

