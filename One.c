//
// Created by anton on 11/30/2020.
//

#include "One.h"

void VControl (FILE *entryfp, FILE *outputfp, struct PBArg *Arg){
	
	int AC=0;
	
	switch (AC=ArgCheck(Arg))
	{
		case 11:
			BG=AOne(entryfp,Arg);
			break;
		
		case 12:
			BG=BOne(entryfp,Arg);
			break;
		
		case 13:
			BG=COne(entryfp,Arg);
			break;
		
		case 14:
			BG=DOne(entryfp,Arg);
			break;
		default:
			Arg->err=1;
			break;
	}
	
	VPrint(outputfp,Arg,AC,BG);
	
	free(Arg);
	return;
}