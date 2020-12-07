#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

#include <stdio.h>

#include "Graph.h"                                                      /* Required because of the struct definitions */

/**********************************************************************************************************************/

char* ExitFileName(char* );                /* Function to create the exit file´s name from the name of the entry file */
int FileCheck(char* );                                  /*  Function to check if an entry file´s name if valid or not */
FILE *RFileOpen (char *);
FILE *WFileOpen(char *);
struct PBArg *ArgRead(FILE*);
struct edge *EdgeRead(FILE *,struct edge *);
int EdgeCheck(int , struct edge *);
void LPrint(FILE *,struct PBArg *,int,double,int);
void EdgePrint(FILE *,struct edge **, int, int);
void EOnePrint(FILE *outputfp, struct graph *g,double sum, int *backup);

/**********************************************************************************************************************/

#endif
