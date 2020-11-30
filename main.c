#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"
#include "Zero.h"
#include "ListGraph.h"



 
int main(int argc, char *argv[])
{
	
	char *EntryFileName, *OutputFileName;
	FILE *EntryFile, *OutputFile;
	struct PBArg *Arg;
	
	if (argc!=2) return 0;
	
	EntryFileName=argv[1];
	
	OutputFileName = ExitFileName(EntryFileName);
	
	EntryFile = RFileOpen(EntryFileName);
	OutputFile = WFileOpen(OutputFileName);
	
	free(OutputFileName);
	
	while (!feof(EntryFile)){
		
		if ((Arg = ArgRead(EntryFile))==NULL){
		
		}
		
		if (Arg->var[1]=='0'){
			
			LControl(EntryFile,OutputFile,Arg);
			
		} else { if (Arg->var[1]=='1'){
			
			VControl(EntryFile,OutputFile,Arg);
			
		} else ErrExit(2);
		
		while(fscanf(EntryFile," ")==1);
	}

	fclose(OutputFile);
	fclose(EntryFile);
	
	return 0;
}


