#ifndef KRUSKAL_INCLUDED
#define KRUSKAL_INCLUDED

#include "Graph.h"

/*CWQU*/
void UFinit(int, int *, int *);

int UFfind(int, int, int *);

void UFunion(int, int, int *, int *);

int lessVertice(const void *, const void *);

int lessCost(const void *, const void *);

/*struct edge BinInit(int);*/
/*
int Bin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double* cost);

int NoBin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double* cost);
*/
/*Kruskal*/
int Kruskal(struct graph *, double* );

void Reverse(struct edge**, int, int);  /* Auxiliary function */

int CWQU(struct edge**, int, double* cost, int *id,int *sz, int);
/*
int NmbrUnion(struct edge** data, int V, int E);
*/
int binsearch(struct edge** ,int*, int*,  int, int);

int N_binsearch(struct edge** data, int *id,int *sz, int start, int end);

#endif
