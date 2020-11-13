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


void LControl (FILE *fp, struct PBArg *Arg);
void AZero(FILE *fp,struct PBArg *Arg);
void BZero(FILE *fp,struct PBArg *Arg);

#endif //AIRROUTES_LIST_H
