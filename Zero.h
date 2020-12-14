/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

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


void LControl (FILE *,FILE *, struct PBArg *);   /* Control of functions that use an array of adjacency lists */
int AZero(FILE *,struct PBArg *);   /* mode A0 */
int BZero(FILE *, struct PBArg *,double *);   /* mode B0 */
int CZero(FILE *,struct PBArg *);   /* mode C0 */
int DZero(FILE *,struct PBArg *);   /* mode D0 */

#endif
