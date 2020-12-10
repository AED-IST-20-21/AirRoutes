#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"

#define OldExt ".routes"                                                            /* Extensions can be changed here */
#define NewExt ".bbones"

/***********************************************************************************************************************
 * Function to create the exit file´s name from the name of the entry file
 * @param FileName Name of the input file
 * @return Name of the Output File
 **********************************************************************************************************************/
char *ExitFileName(char *FileName) {
	char *ExitFileName = NULL;   /* Name of the Output file */
	int FileSize = 0, i;   /* Auxiliary Variable to remove the extension from the entry name */
	
	if (FileCheck(FileName) != 0) exit(1);   /* Checking if the Entry file Name if valid */
	
	
	FileSize = strlen(FileName) - strlen(OldExt) + strlen(NewExt);   /*Determining Size of name without extension*/
	
	if( (ExitFileName = (char*) malloc((FileSize + 1) * sizeof(char))) == NULL)
	{
		ErrExit(3);   /* Memory Allocation for the name of the output file */
	}
	
	strncpy(ExitFileName, FileName,FileSize-strlen(NewExt));   /* Copy name without extension */
	/*strcat(ExitFileName, NewExt);*/   /* Adding Exit Extension */
	for (i= FileSize - strlen(NewExt); i < FileSize; i++)
	{
		ExitFileName[i] = NewExt[i-(FileSize - strlen(NewExt))];
	}

	ExitFileName[FileSize] = '\0';
	
	return ExitFileName;
}

/***********************************************************************************************************************
 * Function to check if an entry file´s name if valid or not
 * @param FileName Name to be checked
 * @return 0 if OK, -1 else
 **********************************************************************************************************************/
int FileCheck(char *FileName) {
	int i;                                                                                      /* Auxiliary Variable */
	int FileSize = strlen(FileName);                                                              /* Size of file name*/
	 /* Run the size of file extension starting from the end of the string because we don´t know the size of the name */
	for (i = FileSize - 1; i > (FileSize - strlen(OldExt)); i--) {
		if (FileName[i] != OldExt[(i - FileSize) + strlen(OldExt)]) {  /* If 1 char isn´t right in the extension exit */
			return -1;
		}
	}
	return 0;
}


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

int EdgeCheck(struct edge *aux, int size) {
	
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

void EdgePrint(FILE *outputfp,struct edge **data, int start, int end) {
	int i;
	for (i = start; i < end; i++) {
		
		fprintf(outputfp,"%d %d %.2lf\n",data[i]->vi,data[i]->vj,data[i]->cost);
		
	}
	return;
}

void EOnePrint(FILE *outputfp, struct graph *g,double sum, int *backup) {
	
	int i;
	
	fprintf(outputfp, "%d %d %s %d %.2lf", g->Arg->v, g->Arg->e, g->Arg->var, g->Arg->v - 1, sum);
	
	for (i = 0; i < g->Arg->v; i++) {
		if (g->data[backup[i]]->vi > 0) {
			
			fprintf(outputfp, "%d %d %.2lf %d %d %.2lf\n", g->data[i]->vi, g->data[i]->vj, g->data[i]->cost,
			        g->data[backup[i]]->vi, g->data[backup[i]]->vj, g->data[backup[i]]->cost);
			
		} else fprintf(outputfp, "%d %d %.2lf -1\n", g->data[i]->vi, g->data[i]->vj, g->data[i]->cost);
		
	}
	return;
}

