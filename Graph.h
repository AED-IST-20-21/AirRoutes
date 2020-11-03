#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct edge Edge;
Edge *EDGE(int, int);

typedef struct graph Graph;

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

#endif // GRAPH_H_INCLUDED
