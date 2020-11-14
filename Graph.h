<<<<<<< HEAD
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct edge Edge;

typedef struct list List;

typedef struct graph {
	
	struct PBArg* Arg;
	void * DataBase;
	
}Graph;


struct PBArg
{

		int v;
		int e;
		int vi;
		int vj;
		char* var;

};


struct list{
	
	int V;
	double cost;
	struct list *next;
	
};


struct edge{
	
	int vi;
	int vj;
	double cost;
};

/* Graph */
Graph *GRAPHinit();
/*Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);*/

/* PBArg */
struct PBArg* PBinit(struct PBArg* );

/* Lista Adjacências */
void GRAPHinsertL(Graph* ,List** );
void GRAPHremoveL(Graph* ,List** );
List* LISTinit(List* );
List* CreateListNode();
void AddList(List* );
void FreeList(List* );
void FreeListV(List**, int );

List *NEW(int v, List *next);

/* Vetor de Arestas */
void GRAPHinsertE(Graph *, Edge *);
void GRAPHremoveE(Graph *, Edge *);

Edge *EDGE(int, int, double );

#endif
=======
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct edge Edge;
Edge *EDGE(int, int);

typedef struct graph {
	
	int Grau;
	struct adj *adj;
	
}Graph;

typedef struct adj{
	
	int V;
	adj *next;
	
};

Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *, Edge *);
void GRAPHremoveE(Graph *, Edge *);
int GRAPHedges(Edge **, Graph *);
Graph *GRAPHcopy(Graph *);
void GRAPHdestroy(Graph *);

link *NEW(int v, link *next);
Graph *GRAPHinit(int V);
void GRAPHinsertE(Graph *G, Edge *e);
void GRAPHremove(Graph *G, Edge *e);
int GRAPHedges(Edge **a, Graph *G);

#endif
>>>>>>> 42f8e001a6feb1086b747c0d365fbc8264867d83
