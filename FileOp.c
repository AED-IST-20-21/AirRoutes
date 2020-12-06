#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"

#define OldExt ".routes"
#define NewExt ".bbones"



/***************************
 * Function to check entry file extension
 * @param FileName Name of the entry file
 * @return 0 if OK, -1 else
 */

int FileCheck(char *FileName) {
	int i;
	int FileSize = strlen(FileName);
	
	for (i = FileSize - 1; i > (FileSize - strlen(OldExt)); i--) {
		if (FileName[i] != OldExt[(i - FileSize) + strlen(OldExt)]) {
			return -1;
		}
	}
	return 0;
}

/********************************
 * Function to add the exit file extension, given the file name with the old extension
 * @param FileName Entry file name
 * @return String with name and extension
 */

char *ExitFileName(char *FileName) {
	char *ExitFileName;
	int FileSize;
	
	if (FileCheck(FileName) != 0)
		exit(0);
	
	FileSize = (strlen(FileName) - strlen(OldExt) + strlen(NewExt));
	if((ExitFileName = (char *) malloc(((FileSize) + 1) * sizeof(char)))==NULL) 
		ErrExit(3);
	
	strcpy(ExitFileName, FileName);
	ExitFileName[strlen(FileName) - strlen(OldExt)] = '\0';
	strcat(ExitFileName, NewExt);
	ExitFileName[FileSize] = '\0';
	
	return ExitFileName;
}

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/

FILE *RFileOpen(char *name) {
	
	FILE *fp = NULL;
	
	if ((fp = fopen(name, "r")) == NULL)
		ErrExit(0);
	
	return fp;
	
}

FILE *WFileOpen(char *name) {
	
	FILE *fp = NULL;
	
	if ((fp = fopen(name, "w")) == NULL)
		ErrExit(0);
	
	
	return fp;
	
}



/*************************************************
 * Function to read one graph problem arguments and store them in the designated struct
 * @param fp File Pointer
 * @param aux empty struct
 * @return aux struct containing all arguments
 */

struct PBArg *ArgRead(FILE *EntryFile) {
	
	struct PBArg *aux = NULL;
	char temp[3];
	
	aux = PBinit();
	
	if (fscanf(EntryFile, " %d %d %s", &aux->v, &aux->e, temp) != 3) {
		aux->err=1;
		return aux;
	}
	
	
	strncpy(aux->var, temp, 2);
	aux->var[2] = '\0';
	
	switch (ArgCheck(aux)) {
		
		case 1: case 3: case 4: case 14:
			if (fscanf(EntryFile, " %d", &aux->vi) != 1) {
				aux->err = 1;
			}
			break;
		
		case 2: case 12: case 13:
			if (fscanf(EntryFile, " %d %d", &aux->vi, &aux->vj) != 2) {
				aux->err = 1;
			}
			break;
			
		case 11:
			break;
		default:
			aux->err = 1;
	}
	
	return aux;
	
}


/*******************************
 * Function to read an edge from file and store it in aux, dinamicaly allocated
 * @param fp File Pointer
 * @return edge read from file
 */

struct edge *EdgeRead(FILE *fp, struct edge *aux) {
	
	int temp;
	
	if ((fscanf(fp, "%d %d %lf", &aux->vi, &aux->vj, &aux->cost) != 3)) {
		
		return NULL;
		
	}
	
	if (aux->vj < aux->vi) {
		
		temp = aux->vj;
		aux->vj = aux->vi;
		aux->vi = temp;
		
	}
	
	return aux;
}

int EdgeCheck(int size, struct edge *aux) {
	
	if ((aux->vi <= 0) || (aux->vj <= 0) || (aux->vi > size) || (aux->vj > size) || (aux->cost <= 0)) return -1;
	else return 0;
}

void LPrint(FILE *outputfp, struct PBArg *Arg, int h, double cost, int mode) {
	
	
	if (mode == 2) {
		if (Arg->err == 0) {
			fprintf(outputfp, "%d %d %s %d %d %.2lf\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, cost);
		} else fprintf(outputfp, "%d %d %s %d %d -1\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
		
	} else if (Arg->err == 0) {
		fprintf(outputfp, "%d %d %s %d %d\n\n", Arg->v, Arg->e, Arg->var, Arg->vi, h);
	} else fprintf(outputfp, "%d %d %s %d -1\n\n", Arg->v, Arg->e, Arg->var, Arg->vi);
	
	return;
	
}

void EdgePrint(FILE *outputfp,struct edge **data, short start, short end) {
	int i;
	for (i = start; i < end; i++) {
		
		fprintf(outputfp,"%d %d %.2lf\n",data[i]->vi,data[i]->vj,data[i]->cost);
		
	}
	return;
}

void EOnePrint(FILE *outputfp, struct graph *g,int sum, int *backup) {
	
	int i;
	
	fprintf(outputfp, "%d %d %s %d %.2lf", g->Arg->v, g->Arg->e, g->Arg->var, g->Arg->v - 1, sum);
	
	for (i = 0; i < g->Arg->v; i++) {
		if (backup[i]->vi > 0) {
			
			fprintf(outputfp, "%d %d %.2lf %d %d %.2lf\n", g->data[i]->vi, g->data[i]->vj, g->data[i]->cost,
			        backup[i]->vi, backup[i]->vj, backup[i]->cost);
			
		} else fprintf(outputfp, "%d %d %.2lf -1\n", g->data[i]->vi, g->data[i]->vj, g->data[i]->cost);
		
	}
	return;
}

