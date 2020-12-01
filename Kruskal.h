#ifndef KRUSKAL_INCLUDED
#define KRUSKAL_INCLUDED

#include "Graph.h"

/*CWQU*/
void UFinit(int, int*, int*);
int UFfind(int, int, int*, int*);
int UFunion(int, int, int*, int*);

int lessVertice(const void*, const void*);
int lessCost(const void*, const void*);
/*struct edge BinInit(int);*/
double Bin(int, int, int*, int*, struct edge*, struct edge*, double);
double NoBin(int, int, int*, int*, struct edge*, struct edge*, double);

/*Kruskal*/
double Kruskal(int, int, struct edge*, struct edge*,
		double (*GoKruskal)(int, int, int*, int*, struct edge*, struct edge*, double));

#endif
