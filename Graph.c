#include <stdlib.h>

#include "Graph.h"



Graph* GraphInit(struct PBArg *Arg)
{
	Graph *G;
	
	if (G = (Graph*) malloc(sizeof(struct graph))==NULL)
		ErrExit(3)
	
	G->Arg = Arg;
	
	return G;
}


/* Lista de Adjacências */
void GRAPHinsertL(Graph *G, List **list)
{
	/*TODO*/
	return;
}

void GRAPHremoveL(Graph *G, List **list)
{
	/*TODO*/
	return;
}

List* LISTinit(List* L)
{
	L = NULL; /*(List*) malloc(sizeof(List));*/
	return L;
}

List* CreateListNode()
{
	List* new = (List*) malloc(sizeof(List));
	return new;
}

void AddList(List* L)
{
	L->next = (List*) CreateListNode();
	return;
}

List** CreateListV(int V)
{
	List** LV = (List**) malloc(V * sizeof(List*));
	return LV;
}

void FreeList(List* L)
{
	List *aux, *Prev;
	aux = L;
	while (aux->next != NULL)
	{
		Prev = aux;
		aux = aux->next;
		free(Prev);
	}
	free(aux);
}

void FreeListV(List** LV, int V)
{
	int i;
	for (i=0; i<V; i++)
	{
		FreeList(LV[i]);
	}
	free(LV);
}

/* Vetor Arestas */
void GRAPHinsertE(Graph *G, Edge *e)
{
	/*int	v = e->v, w = e->w;

	G->adj[v] = NEW(w, G->adj[v]);
	G->adj[w] = NEW(v, G->adj[w]);
	G->E++;*/
}


void GRAPHremoveE(Graph *G, Edge *e)
{
/* Fica como exercício */
}

/*** Transformar Lista de Adjacências em Vetor de Arestas ***/
/*
int GRAPHedges(Edge **a, Graph *G)
{
	int v, E = 0;
	link t;
	for (v = 0; v < G->V; v++)
		for (t = G->adj[v]; t != NULL; t = t->next)
			if (v < t->v )
				a[E++] = EDGE(v, t->v);
	return E;
} TODO (Non essencial) */

