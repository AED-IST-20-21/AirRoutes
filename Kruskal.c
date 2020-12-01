#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "VectorGraph.h" /*Temporary*/

void UFinit(int N, int *id, int *sz) {
	int i;
	
	for (i = 0; i < N; i++) {
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

/* void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
 * qsort(values, 5, sizeof(int), cmpfunc) */


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

struct edge *BinInit(int N) {
	struct edge *bin = (struct edge *) malloc(N * sizeof(struct edge));
	return bin;
}

double Bin(int E, int V, int *id, int *sz, struct edge *mst, struct edge *bin, double cost) {
	int i, k, j;
	
	for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
		if (!UFfind(mst[i].vi, mst[i].vj, id)) {
			UFunion(mst[i].vi, mst[i].vj, id, sz);
			mst[k++] = mst[i];
			cost += mst[i].cost;
		} else {
			bin[j] = mst[i];
			printf("|bin[%d] = %d-%d|\n", j, bin[j].vi, bin[j].vj);
			j++;
		}
	}
	return cost;
}

double NoBin(int E, int V, int *id, int *sz, struct edge *mst, struct edge *bin, double cost) {
	int i, k;
	
	for (i = 0, k = 0; i < E && k < V - 1; i++) {
		if (!UFfind(mst[i].vi, mst[i].vj, id)) {
			UFunion(mst[i].vi, mst[i].vj, id, sz);
			mst[k++] = mst[i];
			cost += mst[i].cost;
		}
	}
	return cost;
}

/**/
void PrintMST(struct edge *mst) {
	int i;
	for (i = 0; i < 10; i++) {
		printf("V->%d\tW->%d\tcost->%lf\t(%d)\n", mst[i].vi, mst[i].vj, mst[i].cost,
		       i + 1);
	}
	printf("\n");
}

/**/

double Kruskal(struct graph *G, struct edge *bin,
               double (*GoKruskal)(int, int, int *, int *, struct edge *, struct edge *, double)) {
	int V = G->Arg->v, E = G->Arg->e;
	
	int *id = (int *) malloc(V * sizeof(int));
	int *sz = (int *) malloc(V * sizeof(int));
	double cost = 0;
	
	qsort(((struct edge **) G->data), E, sizeof(struct edge), lessCost);
	
	UFinit(V, id, sz);
/*
	for (i = 0, k = 0; i < E && k < G->V-1; i++){
		if (!UFfind(mst[i].vi, mst[i].vj, id, sz))
		{
			UFunion(mst[i].vi, mst[i].vj, id, sz);
			mst[k++] = mst[i];
		}
	}
*/
	cost = (*GoKruskal)(E, V, id, sz, G->data, bin, cost);
	
	free(id);
	free(sz);
	return cost;
}

double find(struct PBArg *Arg, struct edge* mst, int* id, bool mode) { /*MODE ON IS B1*/
	
	int i, k, j, V = Arg->v, E = Arg->e;
	int *sz;
	double cost=0;
	struct edge* bindata;

	id = (int *) malloc(V * sizeof(int));
	sz = (int *) malloc(V * sizeof(int));
	
	UFinit(V, id, sz);
			
	bindata=CreateEdgeV(Arg->e-Arg->v+1);

	if (mode) {
		for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
			if ((Arg->vi != mst[i].vi) || (Arg->vi != mst[i].vj)) {	
				if (!UFfind(mst[i].vi, mst[i].vj, id)) {
					
					UFunion(mst[i].vi, mst[i].vj, id, sz);
					mst[k++] = mst[i];
					cost += mst[i].cost;
				} else {
					bindata[j] = mst[i];
					printf("|bin[%d] = %d-%d|\n", j, bindata[j].vi, bindata[j].vj);
					j++;
				}
			}
			/*
			cost = Bin(Arg->e, Arg->v, id, sz, mst, bindata, cost);
			emptybin(bindata, mst, V, E);

			free(id);
			free(sz);
			*/
		}
	} else {
		for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
			if (((Arg->vi != mst[i].vi) && (Arg->vj != mst[i].vj)) ||
			    ((Arg->vj != mst[i].vi) && (Arg->vi != mst[i].vj))) {
				if (!UFfind(mst[i].vi, mst[i].vj, id)) {
					
					UFunion(mst[i].vi, mst[i].vj, id, sz);
					mst[k++] = mst[i];
					cost += mst[i].cost;
				} else {
					bindata[j] = mst[i];
					printf("|bin[%d] = %d-%d|\n", j, bindata[j].vi, bindata[j].vj);
					j++;
				}
			}
		}
	}

	emptybin(bindata, mst, V, E);

	free(sz);

	return cost;
}

