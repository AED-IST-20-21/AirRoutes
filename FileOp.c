#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"
#include "ListGraph.h"

#define OldExt ".routes0"
#define NewExt ".queries"

/***************************
 * Function to check entry file extension
 * @param FileName Name of the entry file
 * @return 0 if OK, -1 else
 */
 
int FileCheck(char* FileName)
{
	int i;
	int FileSize = strlen(FileName);

	for (i = FileSize-1; i > (FileSize-strlen(OldExt)); i--)
	{
		printf("%c-%c\n", FileName[i], OldExt[ (i-FileSize) + strlen(OldExt)]);
		if ( FileName[i] != OldExt[ (i-FileSize) + strlen(OldExt)])
		{
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

char* ExitFileName(char* FileName)
{
	char* ExitFileName;
	int FileSize;

	FileSize = (strlen(FileName) - strlen(OldExt) + strlen(NewExt));
	ExitFileName = (char*) malloc( ((FileSize) + 1) * sizeof(char));

	strcpy(ExitFileName, FileName);
	ExitFileName[strlen(FileName) - strlen(OldExt)]='\0';
	strcat(ExitFileName, NewExt);
	ExitFileName[FileSize] = '\0';

	return ExitFileName;
}

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
FILE *FileOpen (char *FileName,char *mode) {
	
	FILE *fp = NULL;
	
	if (FileCheck(FileName) == 0) {
		if ((fp = fopen(FileName, mode)) == NULL)
			ErrExit(0);
			
		return fp;
		
	} else ErrExit(1);
	
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
			fprintf(stderr,"Error Allocating Memory\n");
			exit(0);
			break;
		case 4:
			fprintf(stderr,"Invalid Arguments\n");
			exit(0);
			break;
		case 5:
			fprintf(stderr,"Error Reading Graph\n");
			exit(0);
			break;
		case 6:
			fprintf(stderr,"Error Reading Edge\n");
			exit(0);
			break;
	}
}

/*************************************************
 * Function to read one graph problem arguments and store them in the designated struct
 * @param fp File Pointer
 * @param aux empty struct
 * @return aux struct containing all arguments
 */
 
struct PBArg *ArgRead(FILE *EntryFile){
	
	struct PBArg *aux=NULL;
	char temp[3];

	aux = PBinit();
	
	fscanf(EntryFile, " %d %d %s", &aux->v, &aux->e, temp);
	
	strncpy(aux->var,temp,2);
	aux->var[2]='\0';
	
	switch (ArgCheck(aux)) {
		
		case 1:fscanf(EntryFile, " %d", &aux->vi);
			break;
			
		case 2:fscanf(EntryFile, " %d %d", &aux->vi, &aux->vj);
			break;
			
		case 3:fscanf(EntryFile, " %d %d", &aux->vi, &aux->vj);
			break;
			
		case 4:fscanf(EntryFile, " %d %d", &aux->vi, &aux->vj);
			break;
			
		default:ErrExit(2);
	}
	
	return aux;
	
}

/********************************
 * Function to check if the problem arguments are valid
 * @param aux Struct containing the problem arguments
 * @return mode if OK -1 else
 */
int ArgCheck (struct PBArg *aux){
	if ((aux->v>0)&&(aux->e>0)){
	
	if (strcmp(aux->var,"A0")==0)
		return 1;

	else if (strcmp(aux->var,"B0")==0)
		return 2;
	
	else if (strcmp(aux->var,"C0")==0)
		return 3;
	
	else if (strcmp(aux->var,"D0")==0)
		return 4;
	
	else return -1;
	
	} else return -1;
}


/*******************************
 * Function to read an edge from file and store it in aux, dinamicaly allocated
 * @param fp File Pointer
 * @return edge read from file
 */
 
struct edge *EdgeRead(FILE *fp,struct edge *aux){
			
	if ((fscanf(fp, "%d %d %lf", &aux->vi, &aux->vj, &aux->cost) != 3)) {
		
	ErrExit(6);
		
	}
	
	return aux;
}

/**************************************************
 * Function to close files and free the graph
 * @param EntryFile Entry File Pointer to close
 * @param OutputFile Output File Pointer to close
 * @param G Graph dinamically allocated to be freed
 */
 
void End(FILE *EntryFile,FILE *OutputFile,struct graph *G,struct PBArg *Arg){
/*	
	fclose(EntryFile);
	fclose(OutputFile);
	GraphFree(G);
	free(Arg);
	*/
	return;
	
}

