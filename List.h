//
// Created by anton on 11/12/2020.
//

#ifndef AIRROUTES_LIST_H
#define AIRROUTES_LIST_H

#include "FileOp.h"
#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>


void LControl (FILE *entryfp,FILE *outputfp, struct PBArg *Arg);
void AZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void BZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void CZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void DZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
#endif //AIRROUTES_LIST_H
