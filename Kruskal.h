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
double Bin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double cost);

double NoBin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double cost);

/*Kruskal*/
double Kruskal(struct graph *G, struct edge **bin,
               double (*GoKruskal)(int, int, int *, int *, struct edge **, struct edge **, double));

double find(struct PBArg *Arg, struct edge **mst,int *id,int *sz);

int binsearch(int*, int*, struct graph* , int);

#endif
