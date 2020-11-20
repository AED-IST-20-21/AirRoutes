#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

#include <stdio.h>

#include "ListGraph.h"


int FileCheck(char* ); /* Checks if FileName is valid */
char* ExitFileName(char* ); /* Creates Exit FileName */
FILE *RFileOpen (char *);
FILE *WFileOpen(char *);
void FileClose(FILE* );
void ErrExit (int err);    /* Function to exit when an error occurs */
/*void End(FILE *EntryFile,FILE *OutputFile,struct graph *G,struct PBArg *Arg);*/

/* PBArg */
struct PBArg *ArgRead(FILE*);
int ArgCheck (struct PBArg *aux);
/*struct PBArg *PBinit(struct PBArg * aux);*/

/* Lista de Adjacências */
/*struct list *ListRead() TODO */

/* Vetor de Arestas */
struct edge *EdgeRead(FILE *fp,struct edge *aux);
int EdgeCheck(int size, struct edge *aux);

#endif
