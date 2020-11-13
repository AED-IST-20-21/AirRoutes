
#include "FileOp.h"


int FileCheck(char* FileName){
return 0;
}//TODO

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
FILE *FileOpen (char *FileName) {
	
	FILE *fp = NULL;
	
	if (FileCheck(FileName) == 0) {
		if ((fp = fopen(FileName, "r")) == NULL)
			FileExit(0);
			
		return fp;
		
	} else FileExit(1);
return fp;
}

/*************************
 * Function to exit when an error occurs
 * @param int err indicating what error occurred
 * @return void
 ************************/
 
void ErrExit (int err) {
	
	switch (err) {
		case 0:
			Dfprintf(stderr, "Error Opening File\n");
			exit(0);
			break;
		case 1:
			Dfprintf(stderr, "Error Checking File Extension\n");
			exit(0);
			break;
		case 2:
			Dfprintf(stderr, "Invalid Mode in Mode fetch\n");
			exit(0);
			break;
		case 3:
			Dfprintf(stderr,"Error Allocating Memory for an edge\n");
			exit(0);
			break;
	}
}

/***********************************
 * Function to print errors only when debugging
 * @param fp File to print
 * @param str Str to print
 */
 
void Dfprintf(FILE *fp, char *str){
	
	if (D==1){
		
		fprintf(fp,str);
		return;
		
	}else {
		
		else fprintf("\n");
		return;
	}
	
}

/*******************************
 * Function to read an edge from file and store it in aux, dinamicaly allocated
 * @param fp File Pointer
 * @return edge read from file
 */
 
struct edge *EdgeRead(FILE *fp){
	
	struct edge *aux;
	
	if((aux=malloc(sizeof(struct edge)))==NULL)
			ErrExit(3)
			
	if (!(fscanf(fp, "%d %d %f", aux->vi, aux->vj, aux->cost) == 3)) {
		
		return NULL;
		
	} else return aux;
}