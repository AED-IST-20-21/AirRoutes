#include <stdlib.h>
#include <stdio.h>

#include "Kruskal.h"
#include "Graph.h"

void UFinit(int V, int *id, int *sz) {
	
	int i;

	for (i = 0; i < V; i++) {
		id[i] = i;
		sz[i] = 1;
	}
}

int UFfind(int p, int q, int *id) {
	int i, j;
	
	for (i = p-1; i != id[i]; i = id[i]);
	for (j = q-1; j != id[j]; j = id[j]);
	if (i == j) {
		return 1;
	} else {
		return 0;
	}
}

void UFunion(int p, int q, int *id, int *sz) {
	int i, j, x, t;
	
	for (i = p-1; i != id[i]; i = id[i]); /*Find root p*/
	for (j = q-1; j != id[j]; j = id[j]); /*Find root q*/
	
	if (sz[i] < sz[j]) {
		id[i] = j;
		sz[j] += sz[i];
		t = j;
	} else {
		id[j] = i;
		sz[i] += sz[j];
		t = i;
	}
	for (i = p-1; i != id[i]; i = x) {
		x = id[i];
		id[i] = t;
	} /*Change root p*/
	for (j = q-1; j != id[j]; j = x) {
		x = id[j];
		id[j] = t;
	} /*Change root q*/
	
}

int lessVertice(const void *a, const void *b) {
	
	struct edge * va, *vb;
	
	va=*(struct edge **)a;
	vb=*(struct edge **)b;
	
	if (va->vi < vb->vi) return 0;
	else if (va->vi == vb->vi) {
		if (va->vj < vb->vj)return 0;
		else return 1;
	} else return 1;
}

int lessCost(const void *a, const void *b) {
	
	struct edge * va, *vb;
	
	va = *(struct edge **)a;
	vb = *(struct edge **)b;

	/*printf("%d %d %lf\n", va->vi, va->vj, va->cost);
	printf("%d %d %lf\n", vb->vi, vb->vj, vb->cost);*/

	if (va->cost > vb->cost) {
		return 1;
	} else {
		return 0;
	}
}
/*
struct edge **BinInit(int N) {
	struct edge **bin = (struct edge **) malloc(N * sizeof(struct edge));
	return bin;
}
*/
#if 0
int Bin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double* cost) {
	int i, k, j, cnt=0;                                                                 /* Kruskal´s Algorithm using the bin */
	
	for (i = 0, k = 0, j = 0; i < E && k < V; i++) {
		if (!UFfind(mst[i]->vi, mst[i]->vj, id)) {
			UFunion(mst[i]->vi, mst[i]->vj, id, sz);
			mst[k++] = mst[i];
			/*printf("mst: %d %d %lf", mst[k-1]->vi, mst[k-1]->vj, mst[k-1]->cost);*/
			*cost += mst[i]->cost;
			cnt++;
		} else {
			bin[j] = mst[i];
			/*printf("|bin[%d] = %d-%d|\n", j, bin[j]->vi, bin[j]->vj);*/
			j++;
		}
	}
	return cnt;
}


int NoBin(int E, int V, int *id, int *sz, struct edge **mst, struct edge **bin, double* cost) {
	int i, k, cnt=0;                                                            /* Kruskal´s Algorithm without using the bin */
	
	for (i = 0, k = 0; i < E && k < V-1 ; i++) {
		if (!UFfind(mst[i]->vi, mst[i]->vj, id)) {
			UFunion(mst[i]->vi, mst[i]->vj, id, sz);
			mst[k++] = mst[i];
			/*printf("mst(i): %d %d %lf\n", mst[k-1]->vi, mst[k-1]->vj, mst[k-1]->cost);*/
			*cost += mst[i]->cost;
			cnt++;
		} else {
			/*printf("Find(i):%d %d %lf\n", mst[i]->vi, mst[i]->vj, mst[i]->cost);*/
		}
	}
	/*printf("\n");*/
	return cnt;
}
#endif
/*
void PrintMST(struct edge **mst) {
	int i;
	for (i = 0; i < 10; i++) {
		printf("V->%d\tW->%d\tcost->%lf\t(%d)\n", mst[i]->vi, mst[i]->vj, mst[i]->cost,
		       i + 1);
	}
	printf("\n");
}
*/
int NmbrUnion(struct edge** data, int V, int E)
{
	int i, k, cnt=0;
	int *id, *sz;

	id = (int*) malloc(V * sizeof(int));
	sz = (int*) malloc(V * sizeof(int));
	
	UFinit(V, id, sz);
	
	for (i = 0, k = 0; i < E && k < V; i++) {
		if (1) {
			if (!UFfind(data[i]->vi, data[i]->vj, id)) {
				
				UFunion(data[i]->vi, data[i]->vj, id, sz);
				cnt++;
			}			
		}
	}
	free(id);
	free(sz);
	return cnt;
}

int Kruskal(struct graph *g,  double* cost)
{
	int V = g->Arg->v, E = g->Arg->e;
	int i, j, k;
	int *id=NULL,*sz=NULL, cnt=0;
	struct edge** mst;

	if ((id = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);
	if ((sz = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);	

	mst = (struct edge**) malloc(E * sizeof(struct edge*));

	UFinit(V, id, sz);  /*Initialization of the id and sz vectors, necessary to CWQU*/
	qsort(g->data, g->Arg->e, sizeof(struct edge*), lessCost);                 /* Sorting the graph */
																   /*Actual kruskal, which depends on the usage of bin*/
	/*cnt = (*GoKruskal)(g->Arg->e, g->Arg->v, id, sz, g->data, bin, cost);*/

	for (i = 0, k = 0, j = E-1; k <= j; i++)
	{
		/*
		mst[i] = (struct edge*) malloc(sizeof(struct edge));
		mst[j] = (struct edge*) malloc(sizeof(struct edge));
		*/
		if (!UFfind(g->data[i]->vi, g->data[i]->vj, id)) {
			UFunion(g->data[i]->vi, g->data[i]->vj, id, sz);
			mst[k++] = g->data[i];
			/*printf("mst: %d %d %lf", mst[k-1]->vi, mst[k-1]->vj, mst[k-1]->cost);*/
			*cost += g->data[i]->cost;
			cnt++;
		} else {
			mst[j] = g->data[i];
			printf("|bin[%d] = %d-%d|\n", j, mst[j]->vi, mst[j]->vj);
			j--;
		}
	}
	
	Reverse(mst, j+1, E-1);
	/*
	for (i=0; i < E; i++)
	{
		free(g->data[i]);		
	}*/
	free(g->data);
	g->data = mst;

	free(id);
	free(sz);
	return cnt;
}

void Reverse(struct edge** mst, int start, int end)
{
	int i, j;
	struct edge* temp;

	for (i=start, j = end; i < j; i++, j--)
	{
		if (mst[i]->cost > mst[j]->cost)
		{
			temp = mst[i];
			mst[i] = mst[j];
			mst[j] = temp;
		}
	}
	return;
}

int CWQU(struct graph *g, double* cost, int *id,int *sz, int Stop) {
	
	int i, cnt = 0;
	
	UFinit(g->Arg->v, id, sz);
	
	for (i = 0; i < Stop; i++) {
		if (g->data[i]->cost > 0) {
			if (!UFfind(g->data[i]->vi, g->data[i]->vj, id))
			{	
				UFunion(g->data[i]->vi, g->data[i]->vj, id, sz);
				*cost += g->data[i]->cost;
				cnt++;
			}
		}
	}	
	return cnt;
}

int binsearch(struct edge** data, int *id,int *sz, int start, int end)
{
	
	int i;
	
	for (i = start; i < end; i++) {
		
		if (!UFfind(((struct edge **)data)[i]->vi, ((struct edge **)data)[i]->vj, id)){
			UFunion(((struct edge **)data)[i]->vi, ((struct edge **)data)[i]->vj, id, sz);
			return i;
		}
	}
	return -1;
}

