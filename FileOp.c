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
	int FileSize, i;   /* Auxiliary Variable to remove the extension from the entry name */
	
	if (FileCheck(FileName) != 0) exit(1);   /* Checking if the Entry file Name if valid */
	
	
	FileSize = strlen(FileName) - strlen(OldExt) + strlen(NewExt);   /*Determining Size of name without extension*/
	
	if ((ExitFileName = (char *) malloc((FileSize + 1) * sizeof(char))) == NULL) {
		ErrExit(3);   /* Memory Allocation for the name of the output file */
	}
	
	strncpy(ExitFileName, FileName, FileSize - strlen(NewExt));   /* Copy name without extension */
	for (i = FileSize - strlen(NewExt); i < FileSize; i++) {
		ExitFileName[i] = NewExt[i - (FileSize - strlen(NewExt))];
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
	int i;  /* Auxiliary Variable */
	int FileSize = strlen(FileName);    /* Size of file name*/
	 /* Run the size of file extension starting from the end of the string because we don´t know the size of the name */
	for (i = FileSize - 1; i > (FileSize - strlen(OldExt)); i--) {
		if (FileName[i] != OldExt[(i - FileSize) + strlen(OldExt)]) {  /* If 1 char isn´t right in the extension exit */
			return -1;
		}
	}
	return 0;
}

/***********************************************************************************************************************
 * Function to read one graph problem arguments and store them in the designated struct
 * @param fp File Pointer
 * @param aux empty struct
 * @return aux struct containing all arguments
 **********************************************************************************************************************/
struct PBArg *ArgRead(FILE *EntryFile) {
	
	struct PBArg *aux = NULL;   /* New struct where arguments are going to be stored */
	char temp[3];   /* Temporary Variable to overcome trouble with fscanf */
	
	aux = PBinit(); /* Initialize Problem Arguments */
	/* Read the arguments that are common to every mode */
	if (fscanf(EntryFile, " %d %d %s", &aux->v, &aux->e, temp) != 3) {
		aux->err=1;   /* Checking if valid read */
		return aux;
	}
	
	strncpy(aux->var, temp, 2); /* More trouble with fscanf */
	aux->var[2] = '\0';
	
	/* From the Common Arguments, we get the mode, with defines how many Arguments to read next */
	switch (ArgCheck(aux)) {
		case 1: case 3: case 4: case 14:    /* Only one extra integer is needed */
			if (fscanf(EntryFile, " %d", &aux->vi) != 1) {
				aux->err = 1;
			}
		break;
		
		case 2: case 12: case 13:   /* Two extra integers needed */
			if (fscanf(EntryFile, " %d %d", &aux->vi, &aux->vj) != 2) {
				aux->err = 1;
			}
		break;
			
		case 11: case 15: /* No extra integers needed */
		break;
		
		default: /* Exception, mode different from any of the supported */
			aux->err = 1;
		break;
	}
	return aux;
}

/***********************************************************************************************************************
 * Function to read an edge from file and store it in aux, dynamically allocated. Sorts the edge by Vertice Criteria
 * @param fp File Pointer
 * @return edge read from file
 **********************************************************************************************************************/
struct edge *EdgeRead(FILE *fp, struct edge *aux) {
	
	 int temp;    /* Temporary Variable needed for the sorting operation */
	
	if ((fscanf(fp, "%d %d %lf", &aux->vi, &aux->vj, &aux->cost) != 3)) return NULL;   /* Checking valid Read */
	
	if (aux->vj < aux->vi) {   /* Checking if the 2nd vertice is smaller than the first */
		
		temp = aux->vj;
		aux->vj = aux->vi;
		aux->vi = temp;
		
	}
	
	return aux;   /* Return the edge */
}

/***********************************************************************************************************************
 * Function to Check if an Edge if valid.
 * @param aux Edge to be checked
 * @param size Number os Vertices in the Graph
 * @return -1 if not OK, 0 if OK
 **********************************************************************************************************************/
int EdgeCheck(struct edge *aux, int size) {
	/* Checks if both vertices are within the limits defined in the Problem Arguments & checks that cost is positive */
	if ((aux->vi <= 0) || (aux->vj <= 0) || (aux->vi > size) || (aux->vj > size) || (aux->cost <= 0)) return -1;
	else return 0;
}

/***********************************************************************************************************************
 * Function that prints the graph in the modes that represent the graph as adjacency list
 * @param outputfp File to write to
 * @param Arg Problem Arguments
 * @param h
 * @param cost Total cost of TODO
 * @param mode
 **********************************************************************************************************************/
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

/***********************************************************************************************************************
 * Function to print all edges from start to finish.
 * @param outputfp File to write to
 * @param data Edge array to print from
 * @param start Start position
 * @param finish End position
 **********************************************************************************************************************/
void EdgePrint(FILE *outputfp,struct edge **data, int start, int finish) {
	
	for (int i = start; i < finish; i++) fprintf(outputfp,"%d %d %.2lf\n",data[i]->vi,data[i]->vj,data[i]->cost);
}
