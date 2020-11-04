#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 
void FileExit (int err) {
	
	switch (err) {
		case 0: fprintf(stderr,"Error Opening File\n");
				exit(0);
			break;
		case 1: fprintf(stderr,"Error Checking File Extension\n");
				exit(0);
			break;
		case 2: fprintf(stderr,"Error allocating argument struct\n");
				exit(0);
			break;
		case 3: fprintf(stderr,"Error Reading Problem Arguments\n");
				exit(0);
			break;
		case 4: fprintf(stderr,"Error Reading Edge Argument\n");
				exit(0);
			break;
		case 5: fprintf(stderr,"Error Allocating New Edge Memory\n");
				exit(0);
			break;
		case 6: fprintf(stderr,"Error Allocating New Graph Memory\n");
				exit(0);
			break;
	}
	
}


/************************************
 * Function to read problem arguments from file
 * @param entry file
 * @return struct with 4 or 5 arguments
 **********************************/
 
struct PBArg ArgumentRead (FILE *fp){

	struct PBArg pb;
	
	if ((pb=malloc(sizeof(struct PBArg)))==NULL) //TODO
		FileExit(2);
	
	if ((fscanf(fp,"%d %d %s %d",pb.V,pb.E,pb.Var,pb.Vi))!=4)
		FileExit(3);
	
	if (strcmp(pb.Var,"B0")==0){
		
		if (fscanf(fp,"%d",pb.Vj)!=1)
			FileExit(3);
		
	} else pb.Vj=-1;
	
	return pb;
}

/*******************************
 * Function to read a new edge from the entry file
 * @param entry file
 * @return struct containing the new edge
 *******************************/

struct edge ReadEdge (FILE *fp){
	
	int i;
	struct edge NewEdge;
	
	NewEdge=CreateEdge();
	
	if ((i=(fscanf(fp,"%d %d %f", NewEdge.vi, NewEdge.vj, NewEdge.cost)))!=3)
		if (i!=0){
			
			FileExit(4);
			
		}else {
			FreeEdge(NewEdge);
			return NULL;
		}
		return NewEdge;
	
}

/************************
 * Function to allocate memory for a new edge
 * @return struct containing new empty edge
 ************************/

struct edge CreateEdge(){ //TODO Mudar função de ficheiro
	
	struct edge NewEdge;
	
	if ((NewEdge=malloc(sizeof(struct edge)))==NULL)
		FileExit(5);
	
	return NewEdge;
	
}

/**********************************
 * Function to Read one graph from file
 * @param fp
 * @return graph containing problem arguments and edges
 *********************************/
 
struct graph GraphRead(FILE *fp){
	
	struct graph NewGraph;
	
	NewGraph=CreateGraph();
	NewGraph->Arg=ArgumentRead(fp);
	
	do {
		
		NewGraph->Edge->next = ReadEdge(fp);
	
	} while (NewGraph.Edge.next!=NULL);
	
	return NewGraph;
}

/**************************
 * Function to allocate memory for one graph
 * @return The new graph
 **************************/
 
struct graph CreateGraph(){ //TODO Mudar função de ficheiro
	
	struct graph NewGraph;
	
	if ((NewGraph=malloc(sizeof(struct graph)))==NULL)
		FileExit(6);
	
	return NewGraph;
	
}