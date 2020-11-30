#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "FileOp.h"
#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

struct graph *LGRead(FILE *, struct PBArg *);
struct list *NewListElement();
void FreeListV(struct list **,int );
void FreeList(struct list* );
struct list* CreateListNode();
struct list* AddList(struct list* );
void PutList(struct list* ,int ,double );
struct list** CreateListV(int );
int LenghtList(struct list *);
int ClickFind(struct list *,int *,int ,int );
int *LampsInit(struct list *,int );

#endif

