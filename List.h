//
// Created by anton on 11/12/2020.
//

#ifndef AIRROUTES_LIST_H
#define AIRROUTES_LIST_H

#include "FileOp.h"
#include "Graph.h"
#include <stdbool.h>



void LControl (FILE *fp, struct PBArg *Arg);
void AZero(FILE *fp,struct PBArg *Arg);
void BZero(FILE *fp,struct PBArg *Arg);
int ModeFetch(struct PBArg Arg);  /* Function to fetch the mode as an integer from the string in the arguments */

#endif //AIRROUTES_LIST_H
