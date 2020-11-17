#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*#include "FileOp.h"*/
#include "Zero.h"
#include "ListGraph.h"

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argc, char *argv[])
{
	
	char *EntryFileName = argv[1],*OutputFileName = "\0";
	FILE *EntryFile,*OutputFile;
	struct PBArg *Arg;
	
	
	EntryFile = FileOpen(EntryFileName,'r');
	OutputFile = FileOpen(OutputFileName,'w');

	do{

		Arg=ArgRead(EntryFile,Arg);
		
		if (Arg->var[1]=='0'){
			
			LControl(EntryFile,OutputFile,Arg);
			
		}else /*if (Arg->var[1]=='1'){
			
			VControl(EntryFile);

		} else*/ ErrExit(2);
		
	}while (!feof(EntryFile));
	
	

	return 0;
}
