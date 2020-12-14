/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#ifndef KRUSKAL_INCLUDED
#define KRUSKAL_INCLUDED

#include "Graph.h"

void UFinit(int, int *, int *);   /* Initialize arrays for CWQU */
int UFfind(int, int, int *);   /* Check for finds in CWQU */
void UFunion(int, int, int *, int *);   /* Add an union to CWQU */
int lessVertice(const void *, const void *);   /* qsort criteria for organizing from smaller to larger vertice */
int lessCost(const void *, const void *);   /* qsort criteria for organizing from smaller to larger cost */
int Kruskal(struct graph *, double* );   /* Full Kruskal´s Algorithm for minimum support tree */
void Reverse(struct edge**, int, int);  /* Reverse the edges that don´t go on the minimum support tree */
int CWQU(struct edge**, int, double* , int *,int *, int);   /* Altered Kruskal that can be stopped at any pos */
int binsearch(struct edge** ,int*, int*,  int, int);   /* Connectivity gap filling */
int N_binsearch(struct edge** , int *,int *, int , int );   /*Connectivity gap filling, ignoring unusable edges */

#endif
