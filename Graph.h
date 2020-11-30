//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_GRAPH_H
#define AIRROUTES_GRAPH_H

struct graph {
	struct PBArg* Arg;
	void* data;
};

struct PBArg {
	int v;
	int e;
	int vi;
	int vj;
	char var[3];
	bool err;
};

struct list{
	int v;
	double cost;
	struct list *next;
};

struct edge{
	int vi;
	int vj;
	double cost;
};

#endif //AIRROUTES_GRAPH_H
