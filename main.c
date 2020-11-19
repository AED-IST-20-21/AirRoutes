#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"
#include "Zero.h"
#include "ListGraph.h"

struct PBArg *Arg;

FILE *ExitFileOpen(char *name);

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argc, char *argv[])
{
	
	char *EntryFileName = argv[1], *OutputFileName;
	FILE *EntryFile, *OutputFile;

	
	OutputFileName = ExitFileName(EntryFileName);

	EntryFile = RFileOpen(EntryFileName);
	OutputFile = WFileOpen(OutputFileName);

	while (feof(EntryFile)!=0) {
/*
		if (feof(EntryFile)!=0)
		{
			printf("Found EOF\n");
			break;
		}
*/
		Arg = ArgRead(EntryFile);

		if (Arg->var[1]=='0'){
			
			LControl(EntryFile, OutputFile, Arg);
			
		} else { /*if (Arg->var[1]=='1'){
			
			VControl(EntryFile);*/

			ErrExit(2);
		}
	}
	
	

	return 0;
}


