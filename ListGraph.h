#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "FileOp.h"
#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

struct graph0 *LGRead(FILE *, struct PBArg *);   /* Read 1 graph and store it as an array of adjacency lists */
struct graph0* Graph0Init();   /* Allocation and initialization of the graph  */
void LGFree(struct graph0 *g);   /* Free the graph allocated as an array of adjacency lists  */
void FreeListV(struct list **,int );   /* Free an array of adjacency lists */
void FreeList(struct list* );   /* Free an adjacency list */
struct list* AddList(struct list* );   /* Allocate and add one more element to the list */
void PutList(struct list* ,int ,double );   /* Put one new element in the list */
struct list** CreateListV(int );   /* Create and allocate a new array of adjacency list */
int LenghtList(struct list *);
int ClickFind(struct list *,int *,int ,int );
int *LampsInit(struct list *,int );

#endif

