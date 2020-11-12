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
	struct PBArg ->CurrentArg;
	
	EntryFile = FileOpen(EntryFileName);
	
	do{
		CurrentArg=ArgRead(EntryFile);
		
		if ((strcmp(CurrentArg->Var[1],'0'))==0){
			
			LControl(EntryFile);
			
		}else if ((strcmp(CurrentArg->Var[1],'1'))==0){
			
			VControl(EntryFile);
		} else {
			
			ErrExit(2);
			
		}
		
	}while (!feof(EntryFile));
	
	fclose(EntryFile);

	return 0;
}
