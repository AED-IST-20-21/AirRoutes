//
// Created by anton on 11/12/2020.
//

#ifndef AIRROUTES_LIST_H
#define AIRROUTES_LIST_H

#include "FileOp.h"
#include "ListGraph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#define CZ 0
#define DZ 1

void LControl (FILE *entryfp,FILE *outputfp, struct PBArg *Arg);
int AZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
int BZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
int CZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
int DZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
int ClickFind(struct list *adj,int *lamps,int size,int j);
int *LampsInit(struct list *lvi,int lenght);
void BadGraph(FILE *);
#endif //AIRROUTES_LIST_H
