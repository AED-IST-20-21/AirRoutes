#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileOp.h"


int FileCheck(char* FileName){
return 0;
}//TODO

/********************************
 * function to open a file when given a filename
 * @param filename
 * @return Pointer to FILE
 *******************************/
 
FILE *FileOpen (char *FileName) {
	
	FILE *fp = NULL;
	
	if (FileCheck(FileName) == 0) {
		if ((fp = fopen(FileName, "r")) == NULL)
			FileExit(0);
			
		return fp;
		
	} else FileExit(1);
return fp;
}

/*************************
 * Function to exit when an error occurs
 * @param int err indicating what error occurred
 * @return void
 ************************/
 
void ErrExit (int err) {
	
	switch (err) {
		case 0:
			Dfprintf(stderr, "Error Opening File\n");
			exit(0);
			break;
		case 1:
			Dfprintf(stderr, "Error Checking File Extension\n");
			exit(0);
			break;
			case
	}
}
/***********************************
 * Function to print errors only when debugging
 * @param fp File to print
 * @param str Str to print
 */
void Dfprintf(FILE *fp, char *str){
	
	if (D==1){
		
		fprintf(fp,str);
		return;
		
	}else {
		
		else fprintf("\n");
		return;
	}
	
}