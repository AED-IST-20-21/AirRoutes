#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"

#define OldExt ".routes0"
#define NewExt ".queries"

int FileCheck(char* FileName)
{
	int i;
	int FileSize = strlen(FileName);

	for (i = FileSize-1; i > (FileSize-strlen(OldExt)); i--)
	{
		/*printf("%c-%c\n", FileName[i], OldExt[FileSize - i]);*/
		if ( FileName[i] != OldExt[ (i-FileSize) + strlen(OldExt)])
		{
			return -1;
		}
	}
	return 0;
}//TODO

char* ExitFileName(char* FileName)
{
	char* ExitFile;
	int FileSize;

	FileSize = (strlen(FileName) - strlen(OldExt) + strlen(NewExt));
	ExitFile = (char*) malloc( ((FileSize) + 1) * sizeof(char));

	strcpy(ExitFile, FileName);
	ExitFile[strlen(FileName) - strlen(OldExt)]='\0';
	strcat(ExitFile, NewExt);
	ExitFile[FileSize] = '\0';

	return ExitFile;
}

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
FILE *FileOpen (char *FileName) {
	
	FILE *fp = NULL;
	
	if (FileCheck(FileName) == 0) {
		if ((fp = fopen(FileName, "r")) == NULL)
			ErrExit(0);
			
		return fp;
		
	} else ErrExit(1);
return fp;
}

/********************************
 * function to close a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
void FileClose(FILE* fp)
{
	fclose(fp);
}

/*************************
 * Function to exit when an error occurs
 * @param int err indicating what error occurred
 * @return void
 ************************/
 
void ErrExit (int err) {
	
	switch (err) {
		case 0:
			fprintf(stderr, "Error Opening File\n");
			exit(0);
			break;
		case 1:
			fprintf(stderr, "Error Checking File Extension\n");
			exit(0);
			break;
		case 2:
			fprintf(stderr, "Invalid Mode\n");
			exit(0);
			break;
		case 3:
			fprintf(stderr,"Error Allocating Memory for an edge\n");
			exit(0);
			break;
		case 4:
			fprintf(stderr,"Invalid Arguments\n");
			exit(0);
			break;
	}
}

/***********************************
 * Function to print errors only when debugging
 * @param fp File to print
 * @param str Str to print
 */

/*
void Dfprintf(FILE *fp, char *str){
	
	if (1){
		
		fprintf(fp, str);
		return;
		
	} else {
		
		fprintf(fp, "\n");
		return;
	}
	
}
*/

/*******************************
 * Function to read an edge from file and store it in aux, dinamicaly allocated
 * @param fp File Pointer
 * @return edge read from file
 */
 
struct edge *EdgeRead(FILE *fp,struct edge *aux){
			
	if ((fscanf(fp, "%d %d %lf", &aux->vi, &aux->vj, &aux->cost) != 3)) {
		
		return NULL;
		
	} else return aux;
}

/*************************************************
 * Function to read one graph problem arguments and store them in the designated struct
 * @param fp File Pointer
 * @param aux empty struct
 * @return aux struct containing all arguments
 */
struct PBArg *ArgRead(FILE *fp,struct PBArg *aux){
	
	if ((fscanf(fp, "%d %d %s", &aux->v, &aux->e, aux->var) != 3)) {
		
		ErrExit(4);
		
	} else if ((strcmp(aux->var,"A0"))!=0){
		
		if ((fscanf(fp, "%d %d", &aux->vi, &aux->vj) != 2))
			ErrExit(4);
		
	}else {
		
		if ((fscanf(fp, "%d", &aux->vi) != 1))
			ErrExit(4);
	
	}
	
	if(ArgCheck(aux)!=0)
		ErrExit(4);
	
	return aux;
	
}

/********************************
 * Function to check if the problem arguments are valid
 * @param aux Struct containing the problem arguments
 * @return 0 if OK -1 else
 */
int ArgCheck (struct PBArg *aux){
	if ((aux->v>0)&&(aux->e>0)){
	
	if ( (strcmp(aux->var,"A0")!=0) && (aux->vi>0) )
		return 0;

	else if( (strcmp(aux->var,"B0")!=0) && (aux->vi>0) && (aux->vj>0) )
		return 0;
	
	else if( (strcmp(aux->var,"C0")!=0) && (aux->vi>0) && (aux->vj>0) )
		return 0;
	
	else if( (strcmp(aux->var,"D0")!=0) && (aux->vi>0) && (aux->vj>0) )
		return 0;
	
	else return -1;
	
	} else return -1;
}

/**********************
 * Memory allocation and Initialization of PBArg
 * @return clean PBArg
 *********************/
struct PBArg * PBInit(struct PBArg * aux){
	
	if (aux==NULL){
		if ((aux = (struct PBArg* ) malloc(sizeof(struct PBArg)))==NULL){
		
			ErrExit(3);
		}
	}
	
	aux->v=0;
	aux->e=0;
	aux->vi=0;
	aux->vj=0;
	aux->var='\0';
	
	return aux;
}
