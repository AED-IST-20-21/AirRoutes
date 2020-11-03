#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

struct PBArg{
	
	int V;
	int E;
	int Vi;
	int Vj;
	char *Var;
	
};  /* Struct storing the current problem arguments */

typedef struct edge {
	
	int vi;
	int vj;
	double cost;
	
};

FILE *FileOpen (char *filename);    /* Function to Open a File */
void FileExit (int err);    /* Function to exit when an error occurs */
struct PBArg ArgumentRead (FILE *fp);   /*Function to Read problem Arguments */
struct edge ReadEdge (FILE *fp); /* Function to read a new edge */
struct edge CreateEdge(); /* Function to allocate memory for a new edge struct */

#endif //AIRROUTES_FILEOP_H
