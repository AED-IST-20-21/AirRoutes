//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_VECTORGRAPH_H
#define AIRROUTES_VECTORGRAPH_H

#include "FileOp.h"
#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

struct graph *VGRead(FILE *, struct PBArg *);
int lessVertice(const void *,const void *);
struct edge **CreateEdgeV(int );

#endif //AIRROUTES_VECTORGRAPH_H
