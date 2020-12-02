#ifndef KRUSKAL_INCLUDED
#define KRUSKAL_INCLUDED

#include "Graph.h"

/*CWQU*/
void UFinit(int, int *, int *);

int UFfind(int, int, int *);

int UFunion(int, int, int *, int *);

int lessVertice(const void *, const void *);

int lessCost(const void *, const void *);

/*struct edge BinInit(int);*/
double Bin( struct graph *g,int *id, int *sz, struct edge **bin);
double NoBin(struct graph *g,int *id, int *sz, struct edge **bin);


/*Kruskal*/
double Kruskal(struct graph *G, struct edge **bin,
               double (*GoKruskal)(struct graph *, int *, int *, struct edge **));

double find(struct PBArg *Arg, struct edge **mst,int *id,int *sz);
#endif
