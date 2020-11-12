#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

struct PBArg{
	
	int V;
	int E;
	int Vi;
	int Vj;
	char *Var;
	
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
void FileExit (int err);    /* Function to exit when an error occurs */

#endif
