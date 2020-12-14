/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#ifndef AIRROUTES_ONE_H
#define AIRROUTES_ONE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

#include "FileOp.h"
#include "Graph.h"
#include "VectorGraph.h"
#include "Kruskal.h"

void VControl (FILE *, FILE *, struct PBArg *);  /* Control for all modes that represent the graph as an edge array */
void AOne(FILE *, FILE *, struct PBArg *);   /* Mode A1 */
void BOne(FILE *, FILE *, struct PBArg *);   /* Mode B1 */
void COne(FILE *, FILE *, struct PBArg *);   /* Mode C1 */
void DOne(FILE *, FILE *, struct PBArg *);   /* Mode D1 */
void EOne(FILE *, FILE *, struct PBArg *);   /* Mode E1 */


#endif //AIRROUTES_ONE_H

