//
// Created by anton on 11/12/2020.
//

#ifndef AIRROUTES_LIST_H
#define AIRROUTES_LIST_H

#include "FileOp.h"
#include "ListGraph.h"
#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#define CZ 0
#define DZ 1

void LControl (FILE *,FILE *, struct PBArg *);
int AZero(FILE *,struct PBArg *);
int BZero(FILE *, struct PBArg *,double *);
int CZero(FILE *,struct PBArg *);
int DZero(FILE *,struct PBArg *);

#endif //AIRROUTES_LIST_H
