#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

link *NEW(int v, link *next);
Graph *GRAPHinit(int V);
void GRAPHinsertE(Graph *G, Edge *e);
void GRAPHremove(Graph *G, Edge *e);
int GRAPHedges(Edge **a, Graph *G);

#endif // GRAPH_H_INCLUDED
