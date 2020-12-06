#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

#include <stdio.h>

/*#include "ListGraph.h"*/
#include "Graph.h"


int FileCheck(char* );
char* ExitFileName(char* );
FILE *RFileOpen (char *);
FILE *WFileOpen(char *);
struct PBArg *ArgRead(FILE*);
int ArgCheck (struct PBArg *);
struct edge *EdgeRead(FILE *,struct edge *);
int EdgeCheck(int , struct edge *);
void LPrint(FILE *,struct PBArg *,int,double,int);
void EdgePrint(FILE *,struct edge **, short, short);
void EOnePrint(FILE *outputfp, struct graph *g,int sum, int *backup);

#endif
