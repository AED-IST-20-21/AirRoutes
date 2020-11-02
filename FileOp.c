
#include "FileOp.h"

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
FILE *FileOpen (char *filename) {
	
	FILE *fp;
	
	if (FileCheck(filename) == 0) {
		if ((fp = fopen(filename, 'r')) == NULL)
			FileExit(0);
			
		return fp;
		
	} else FileExit(1);
}

/*************************
 * Function to exit when an error occurs
 * @param int err indicating what error occurred
 * @return void
 ************************/
 
void FileExit (int err) {
	
	switch (err) {
		case 0: printf("Error Opening File\n");
				exit(0);
			break;
		case 1: printf("Error Checking File Extension\n");
				exit(0);
			break;
		case 2: printf("Error allocating argument struct\n");
				exit(0);
			break;
		case 3: printf("Error Reading Problem Arguments\n");
				exit(0);
			break;
		case 4: printf("Error Reading Edge Argument\n");
				exit(0);
			break;
		case 5: printf("Error Allocating New Edge Memory\n");
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
	
	struct edge NewEdge;
	
	NewEdge=CreateEdge();
	
	if ((fscanf(fp,"%d %d %f", NewEdge.vi, NewEdge.vj, NewEdge.cost))!=3)
		FileExit(4);
	
	return NewEdge;
	
}

/************************
 * Function to allocate memory for a new edge
 * @return struct containing new empty edge
 ************************/
 
struct edge CreateEdge(){
	
	struct edge NewEdge;
	
	if ((NewEdge=malloc(sizeof(struct edge)))==NULL)
		FileExit(5);
	
	return NewEdge;
	
}