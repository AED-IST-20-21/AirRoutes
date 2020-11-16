#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*#include "FileOp.h"*/
#include "List.h"
#include "Graph.h"

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argc, char *argv[])
{
	
	char *EntryFileName = "\0";
	FILE *EntryFile;
	Graph* G;
	/*struct PBArg ->CurrentArg;*/
	
	EntryFile = FileOpen(EntryFileName);
	
	G = GRAPHinit();

	do{

		G->Arg=ArgRead(EntryFile, G->Arg);
		
		if (G->Arg->var[1]=='0'){
			
			LControl(EntryFile, G->Arg);
			
		}else if (G->Arg->var[1]=='1'){
			
			/*VControl(EntryFile);*/

		} else {
			
			ErrExit(2);
			
		}
		
	}while (!feof(EntryFile));
	
	fclose(EntryFile);

	return 0;
}
