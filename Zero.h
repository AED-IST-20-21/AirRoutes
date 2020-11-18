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

#define ON 1
#define OFF 0
#define CZ 0
#define DZ 1

void LControl (FILE *entryfp,FILE *outputfp, struct PBArg *Arg);
void AZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void BZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void CZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
void DZero(FILE *entryfp,FILE *outputfp,struct PBArg *Arg);
int FindList(struct list *, int );
int ClickFind(struct list *, struct list* );
#endif //AIRROUTES_LIST_H
