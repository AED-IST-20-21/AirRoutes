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
	struct edge *next;
	
}; /* Struct storing an edge */

struct graph {
	
	struct PBArg *Arg;
	struct edge *Edge;
	
};

FILE *FileOpen (char *FileName);    /* Function to Open a File */
void FileExit (int err);    /* Function to exit when an error occurs */
struct PBArg ArgumentRead (FILE *fp);   /*Function to Read problem Arguments */
struct edge ReadEdge (FILE *fp); /* Function to read a new edge */
struct edge CreateEdge(); /* Function to allocate memory for a new edge struct */
struct graph GraphRead(FILE *fp);
struct graph CreateGraph();

#endif //AIRROUTES_FILEOP_H
