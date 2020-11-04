#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

typedef struct {
	
	int V;
	int E;
	int Vi;
	int Vj;
	char *Var;
	
} PBArg ;  /* Struct storing the current problem arguments */

typedef struct edge {
	
	int vi;
	int vj;
	double cost;
	struct edge *next;
	
}; /* Struct storing an edge */

typedef struct graph {
	
	struct PBArg;
	struct *edge;
	
};

FILE *FileOpen (char *FileName);    /* Function to Open a File */
void FileExit (int err);    /* Function to exit when an error occurs */
struct PBArg ArgumentRead (FILE *fp);   /*Function to Read problem Arguments */
struct edge ReadEdge (FILE *fp); /* Function to read a new edge */
struct edge CreateEdge(); /* Function to allocate memory for a new edge struct */


#endif //AIRROUTES_FILEOP_H
