#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

#include <stdio.h>

#include "Graph.h"

/*
struct PBArg{
	
	int v;
	int e;
	int vi;
	int vj;
	char *var;
	
} ;*/  /* Struct storing the current problem arguments */
/*
struct edge {
	
	int vi;
	int vj;
	double cost;
	
}; */ /* Struct storing an edge */

/*
struct graph {
	
	struct PBArg *Arg;
	void * DataBase;
	
};
*/

int FileCheck(char* ); /* Checks if FileName is valid */
char* ExitFileName(char* ); /* Creates Exit FileName */
FILE *FileOpen (char *FileName);    /* Function to Open a File */
void FileClose(FILE* );
void ErrExit (int err);    /* Function to exit when an error occurs */
void Dprintf(FILE* , char* ); /* TODO */

/* PBArg */
struct PBArg *ArgRead(FILE *fp,struct PBArg *aux);
int ArgCheck (struct PBArg *aux);

/* Lista de Adjacências */
/*struct list *ListRead() TODO */

/* Vetor de Arestas */
struct edge *EdgeRead(FILE *fp,struct edge *aux);

#endif
