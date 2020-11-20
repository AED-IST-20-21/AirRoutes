#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"
#include "Zero.h"
#include "ListGraph.h"

struct PBArg *Arg;

 
int main(int argc, char *argv[])
{
	
	char *EntryFileName = argv[1], *OutputFileName;
	FILE *EntryFile, *OutputFile;

	
	OutputFileName = ExitFileName(EntryFileName);

	EntryFile = RFileOpen(EntryFileName);
	OutputFile = WFileOpen(OutputFileName);
	
	while (!feof(EntryFile)){
		
		Arg = ArgRead(EntryFile);
		
		if (Arg->var[1]=='0'){
			
			LControl(EntryFile,OutputFile,Arg);
			
		} else { /*if (Arg->var[1]=='1'){
			
			VControl(EntryFile);*/
			
			ErrExit(2);
		}
		
		while(fscanf(EntryFile," ")==1);
	}
	End(OutputFileName,OutputFile,EntryFile);
	return 0;
}


