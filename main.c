#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"
#include "Zero.h"
#include "ListGraph.h"

struct PBArg *Arg;

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

	EntryFile = FileOpen(EntryFileName,"r");
	OutputFile = fopen(OutputFileName,"w");

	/*
	fp = fopen(EntryFileName, "r");
	fscanf(fp, "%d", &i);
	printf("VERIFICATION - %d\n", i);
	fclose(fp);*/

	do{

		Arg = ArgRead(EntryFile);
		
		if (Arg->var[1]=='0'){

			printf("Entering LControl...\n");
			LControl(EntryFile,OutputFile,Arg);
			
		}else /*if (Arg->var[1]=='1'){
			
			VControl(EntryFile);

		} else*/ ErrExit(2);
		
	}while (!feof(EntryFile));
	
	

	return 0;
}
