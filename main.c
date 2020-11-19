#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"
#include "Zero.h"
#include "ListGraph.h"

struct PBArg *Arg;

 
int main( int argc,char *argv[])
{
	
	char *EntryFileName = argv[1], *OutputFileName;
	FILE *EntryFile, *OutputFile;

	
	OutputFileName = ExitFileName(EntryFileName);

	EntryFile = RFileOpen(EntryFileName);
	OutputFile = WFileOpen(OutputFileName);

	do{

		Arg = ArgRead(EntryFile);
		
		if (Arg->var[1]=='0'){
			
			LControl(EntryFile,OutputFile,Arg);
			
		}else /*if (Arg->var[1]=='1'){
			
			VControl(EntryFile);

		} else*/ ErrExit(2);
		
	}while (feof(EntryFile)==0);
	
	

	return 0;
}


