#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argv, char **argc)
{
	
	char *EntryFileName = "\0";
	FILE *EntryFile;
	struct graph Current;
	
	EntryFile = FileOpen(EntryFileName);
	
	do{
	
	Current=GraphRead(EntryFile);
			
			/*Trabalhar no grafo*/
		
	}while (!feof(EntryFile));
	
	fclose(EntryFile);

	return 0;
}
