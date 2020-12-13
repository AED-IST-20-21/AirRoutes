#ifndef AIRROUTES_FILEOP_H
#define AIRROUTES_FILEOP_H

#include <stdio.h>

#include "Graph.h"   /* Required for struct definitions */

/**********************************************************************************************************************/

char* ExitFileName(char* );   /* Create Exit file name */
int FileCheck(char* );   /* Checks if Entry file has the right extension */
struct PBArg *ArgRead(FILE*);   /* Read Arguments from entry file */
struct edge *EdgeRead(FILE *,struct edge *);   /* Read Edge from entry file */
int EdgeCheck(struct edge *, int);   /* Checks if an edge is valid */
void LPrint(FILE *,struct PBArg *,int,double,int);   /* Prints output in mode 0 */
void EdgePrint(FILE *,struct edge **, int, int);   /* Print all edges in given interval */
void EOnePrint(FILE *outputfp, struct graph *g,double sum, int *backup);   /*  */

/**********************************************************************************************************************/

#endif
