#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "VectorGraph.h"

void UFinit(int V, int *id, int *sz) {
	
	int i;
	
	if ((id = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);
	if ((sz = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);
	
	for (i = 0; i < V; i++) {
		id[i] = i;
		sz[i] = 1;
	}
}

int UFfind(int p, int q, int *id) {
	int i, j;
	
	for (i = p; i != id[i]; i = id[i]);
	for (j = q; j != id[j]; j = id[j]);
	if (i == j) {
		return 1;
	} else {
		return 0;
	}
}

void UFunion(int p, int q, int *id, int *sz) {
	int i, j, x, t;
	
	for (i = p; i != id[i]; i = id[i]); /*Find root p*/
	for (j = q; j != id[j]; j = id[j]); /*Find root q*/
	
	if (sz[i] < sz[j]) {
		id[i] = j;
		sz[j] += sz[i];
		t = j;
	} else {
		id[j] = i;
		sz[i] += sz[j];
		t = i;
	}
	for (i = p; i != id[i]; i = x) {
		x = id[i];
		id[i] = t;
	} /*Change root p*/
	for (j = q; j != id[j]; j = x) {
		x = id[j];
		id[j] = t;
	} /*Change root q*/
	
}

int lessVertice(const void *a, const void *b) {
	
	if (((struct edge *) a)->vi < ((struct edge *) b)->vi) return 0;
	else if (((struct edge *) a)->vi == ((struct edge *) b)->vi) {
		if (((struct edge *) a)->vj < ((struct edge *) b)->vj)return 0;
		else return 1;
	} else return 1;
}

int lessCost(const void *a, const void *b) {
	if (((struct edge *) a)->cost > ((struct edge *) b)->cost) {
		return 1;
	} else {
		return 0;
	}
}

struct edge **BinInit(int N) {
	struct edge **bin = (struct edge **) malloc(N * sizeof(struct edge));
	return bin;
}

double Bin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double cost) {
	int i, k, j;                                                                 /* Kruskal´s Algorithm using the bin */
	
	for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
		if (!UFfind(mst[i]->vi, mst[i]->vj, id)) {
			UFunion(mst[i]->vi, mst[i]->vj, id, sz);
			mst[k++] = mst[i];
			cost += mst[i]->cost;
		} else {
			bin[j] = mst[i];
			printf("|bin[%d] = %d-%d|\n", j, bin[j]->vi, bin[j]->vj);
			j++;
		}
	}
	return cost;
}

double NoBin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double cost) {
	int i, k;                                                            /* Kruskal´s Algorithm without using the bin */
	
	for (i = 0, k = 0; i < E && k < V - 1; i++) {
		if (!UFfind(mst[i]->vi, mst[i]->vj, id)) {
			UFunion(mst[i]->vi, mst[i]->vj, id, sz);
			mst[k++] = mst[i];
			cost += mst[i]->cost;
		}
	}
	return cost;
}

void PrintMST(struct edge **mst) {
	int i;
	for (i = 0; i < 10; i++) {
		printf("V->%d\tW->%d\tcost->%lf\t(%d)\n", mst[i]->vi, mst[i]->vj, mst[i]->cost,
		       i + 1);
	}
	printf("\n");
}

double Kruskal(struct graph *g, struct edge **bin,
		double (*GoKruskal)(int, int, int *, int *, struct edge **, struct edge **, double)) {
	
	int *id,*sz;
	double cost = 0;
	
	UFinit(g->Arg->v, id, sz);                            /*Initialization of the id and sz vectors, necessary to CWQU*/
	qsort(((struct edge **) g->data), g->Arg->e, sizeof(struct edge), lessCost);                 /* Sorting the graph */
																   /*Actual kruskal, which depends on the usage of bin*/
	cost = (*GoKruskal)(g->Arg->e, g->Arg->v, id, sz, g->data, bin, cost);
	
	free(id);
	free(sz);
	return cost;
}

double find(struct PBArg *Arg, struct edge **mst,int *id,int *sz) {
	
	int i, k, j, V = Arg->v, E = Arg->e;

	double cost = 0;
	struct edge **bindata;
	
	
	
	UFinit(V, id, sz);
	
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	
	for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
		if (mst[i]->cost < 0) {
			if (!UFfind(mst[i]->vi, mst[i]->vj, id)) {
				
				UFunion(mst[i]->vi, mst[i]->vj, id, sz);
				mst[k++] = mst[i];
				cost += mst[i]->cost;
			} else {
				bindata[j] = mst[i];
				printf("|bin[%d] = %d-%d|\n", j, bindata[j]->vi, bindata[j]->vj);
				j++;
			}
		}
	}
	
	emptybin(bindata, mst, V, E);
	return cost;
}

