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

double Bin( struct graph *g,int *id, int *sz, struct edge **bin) {
	int i, k, j;
	double sum = 0;                /* Kruskal´s Algorithm using the bin */
	
	for (i = 0, k = 0, j = 0; i < g->Arg->e && k < g->Arg->v; i++) {
		if (!UFfind(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id)) {
			UFunion(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id, sz);
			((struct edge **)g->data)[k++] = ((struct edge **)g->data)[i];
			sum += ((struct edge **)g->data)[i]->cost;
		} else {
			bin[j] = ((struct edge **)g->data)[i];
			printf("|bin[%d] = %d-%d|\n", j, bin[j]->vi, bin[j]->vj);
			j++;
		}
	}
	return sum;
}
double NoBin(struct graph *g,int *id, int *sz, struct edge **bin) {
	int i, k;
	double cost = 0;            /* Kruskal´s Algorithm without using the bin */
	
	for (i = 0, k = 0; i < g->Arg->e && k < g->Arg->v - 1; i++) {
		if (!UFfind(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id)) {
			UFunion(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id, sz);
			((struct edge **)g->data)[k++] = ((struct edge **)g->data)[i];
			cost += ((struct edge **)g->data)[i]->cost;
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
		double (*GoKruskal)(struct graph *, int *, int *, struct edge **)) {
	
	int *id,*sz;
	double cost = 0;
	
	UFinit(g->Arg->v, id, sz);                            /*Initialization of the id and sz vectors, necessary to CWQU*/
	qsort(((struct edge **) g->data), g->Arg->e, sizeof(struct edge), lessCost);                 /* Sorting the graph */
																   /*Actual kruskal, which depends on the usage of bin*/
	cost = (*GoKruskal)(g, id, sz, bin);
	
	free(id);
	free(sz);
	return cost;
}

double find(struct graph *g,int *id,int *sz) {
	
	int i, k, j;

	double cost = 0;
	struct edge **bindata;
	
	
	
	UFinit(g->Arg->v, id, sz);
	
	bindata = CreateEdgeV(g->Arg->e - g->Arg->v + 1);
	
	for (i = 0, k = 0, j = 0; i < g->Arg->e && k < g->Arg->v; i++) {
		if (((struct edge **)g->data)[i]->cost < 0) {
			if (!UFfind(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id)) {
				
				UFunion(((struct edge **)g->data)[i]->vi, ((struct edge **)g->data)[i]->vj, id, sz);
				((struct edge **)g->data)[k++] = ((struct edge **)g->data)[i];
				cost += ((struct edge **)g->data)[i]->cost;
			} else {
				bindata[j] = ((struct edge **)g->data)[i];
				printf("|bin[%d] = %d-%d|\n", j, bindata[j]->vi, bindata[j]->vj);
				j++;
			}
		}
	}
	
	emptybin(bindata,g);
	return cost;
}

