#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

struct PBArg{
	
	int v;
	int e;
	int vi;
	int vj;
	char *var;
	
} ;  /* Struct storing the current problem arguments */

struct edge {
	
	int vi;
	int vj;
	double cost;
	
}; /* Struct storing an edge */

struct graph {
	
	struct PBArg *Arg;
	struct edge *Edge;
	
};

FILE *FileOpen (char *FileName);    /* Function to Open a File */
void ErrExit (int err);    /* Function to exit when an error occurs */
struct edge *EdgeRead(FILE *fp);
#endif
