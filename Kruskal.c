#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

void UFinit(int N, int* id, int* sz)
{
	int i;

	for (i = 0; i < N; i++) {
		id[i] = i; sz[i] = 1;
	}
}

int UFfind(int p, int q, int* id, int* sz)
{
	int i, j;

	for (i = p; i != id[i]; i = id[i]);
	for (j = q; j != id[j]; j = id[j]);
	if (i == j){
		return 1;
	} else {
		return 0;
	}
}

void UFunion(int p, int q, int* id, int* sz)
{
	int i, j, x, t;

	for (i = p; i != id[i]; i = id[i]); /*Find root p*/
	for (j = q; j != id[j]; j = id[j]); /*Find root q*/

	if (sz[i] < sz[j]) {
		id[i] = j; sz[j] += sz[i]; t = j;	
	} else {
		id[j] = i; sz[i] += sz[j]; t = i;
	}
	for (i = p; i != id[i]; i = x) {x = id[i]; id[i] = t;} /*Change root p*/
	for (j = q; j != id[j]; j = x) {x = id[j]; id[j] = t;} /*Change root q*/

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

int lessCost(const void* a, const void* b)
{
	if ( ((struct edge*) a)->cost > ( (struct edge*) b )->cost )
	{
		return 1;
	} else {
		return 0;
	}
}

struct edge* BinInit(int N)
{
	struct edge* bin = (struct edge* ) malloc(N * sizeof(struct edge));
	return bin;
}

double Bin(int E, int V, int* id, int* sz, struct edge* mst, struct edge* bin, double cost)
{
	int i, k, j;

	for (i = 0, k = 0, j=0; i < E && k < V; i++){
		if (!UFfind(mst[i].vi, mst[i].vj, id, sz))
		{
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

double NoBin(int E, int V, int* id, int* sz, struct edge* mst, struct edge* bin, double cost)
{
	int i, k;

	for (i = 0, k = 0; i < E && k < V-1; i++){
		if (!UFfind(mst[i].vi, mst[i].vj, id, sz))
		{
			UFunion(mst[i].vi, mst[i].vj, id, sz);
			mst[k++] = mst[i];
			cost += mst[i].cost;
		}
	}
	return cost;
}

/**/
void PrintMST(struct edge* mst)
{
	int i;
	for (i=0; i<10; i++)
	{
		printf("V->%d\tW->%d\tcost->%lf\t(%d)\n", mst[i].vi, mst[i].vj, mst[i].cost,
				i+1);
	}
	printf("\n");
}
/**/

double Kruskal(int V, int E, struct edge mst[], struct edge* bin,
 double (*GoKruskal)(int, int, int*, int* , struct edge*, struct edge*, double))
{
	int N = V;

	int *id = (int *) malloc(N * sizeof(int));
	int *sz = (int *) malloc(N * sizeof(int));
	double cost=0;

	qsort(mst, E, sizeof(struct edge), lessCost);
	/*PrintMST(mst);*/
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
	cost = (*GoKruskal)(E, N, id, sz, mst, bin, cost);

	free(id);
	free(sz);
	return cost;
}

/*
int main(int argc, char* argv[])
{
	int E=10, V=8, N=atoi(argv[1]);
	struct edge TestMe[10];
	struct edge* bin;

	TestMe[0].v = 1;
	TestMe[0].vj = 2;
	TestMe[0].cost = 20.5;

	TestMe[1].v = 1;
	TestMe[1].vj = 4;
	TestMe[1].cost = 9.22;

	TestMe[2].v = 2;
	TestMe[2].vj = 6;
	TestMe[2].cost = 11.7;

	TestMe[3].v = 2;
	TestMe[3].vj = 7;
	TestMe[3].cost = 3.68;

	TestMe[4].v = 3;
	TestMe[4].vj = 5;
	TestMe[4].cost = 4.0;

	TestMe[5].v = 4;
	TestMe[5].vj = 5;
	TestMe[5].cost = 3.96;

	TestMe[6].v = 4;
	TestMe[6].vj = 6;
	TestMe[6].cost = 5.3;

	TestMe[7].v = 4;
	TestMe[7].vj = 7;
	TestMe[7].cost = 5.2;

	TestMe[8].v = 4;
	TestMe[8].vj = 8;
	TestMe[8].cost = 4.8;

	TestMe[9].v = 6;
	TestMe[9].vj = 8;
	TestMe[9].cost = 5.1;

	if(N==1){	
		
		bin = BinInit(E-V+1);
		Kruskal(V,E, TestMe, bin, Bin);

		printf("\nBin Active\n");
		for (V=0; V<3; V++)
		{
			TestMe[7+V] = bin[V];
			printf("|bin[%d] = %d-%d|\n", V, bin[V].vi, bin[V].vj);
		}
		printf("\n");
		
		PrintMST(TestMe);
		free(bin);

	} else {
	
		Kruskal(V,E, TestMe, NULL, NoBin);
		PrintMST(TestMe);
	}

	return 0;
}
*/
