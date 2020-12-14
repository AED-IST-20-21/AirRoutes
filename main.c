/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Zero.h"
#include "One.h"

/***********************************************************************************************************************
 * Main Function of the Program Backbones
 * @param argc Number of Arguments passed from the Terminal
 * @param argv Vector of strings containing each argument passed from the Terminal
 * @return 0 if successful operation
 **********************************************************************************************************************/
int main(int argc, char *argv[]) {
	
	char *EntryFileName = NULL, *OutputFileName = NULL;   /* File Names */
	FILE *EntryFile, *OutputFile;   /* File Pointers */
	struct PBArg *Arg;   /* Current Problem Arguments */
	
	if (argc != 2) return 0;   /* Exit program if number of arguments is different than desired */

/********************************************* Initialization *********************************************************/
	
	/* Setting File names */
	EntryFileName = (char*) malloc((strlen(argv[1]) + 1) * sizeof(char));
	strcpy(EntryFileName,argv[1]);  /* Store Entry file´s name */
	OutputFileName = ExitFileName(EntryFileName);    /* Create exit file´s name */
	/* Opening Files */
	if ((EntryFile = fopen(EntryFileName, "r")) == NULL) ErrExit(0); /* Open Entry File on Read Mode */
	if ((OutputFile= fopen(OutputFileName, "w")) == NULL) ErrExit(0);   /* Open Exit File on Write Mode */
	free(OutputFileName);   /* Once the files are open, their names can be discarded */
	free(EntryFileName);
	
/********************************************* Problem Solving ********************************************************/
	
	while (!feof(EntryFile)) {   /* While End of File isn´t reached, work on the next problem */
		
		if ((Arg = ArgRead(EntryFile)) == NULL) break;
		
		if (Arg->var[1] == '0') {   /* If problem from mode 0, resolve with adjacency list */
			
			LControl(EntryFile, OutputFile, Arg);
			
		} else if (Arg->var[1] =='1') {   /* If problem from mode 1, resolve with edge vector */
			
			VControl(EntryFile, OutputFile, Arg);
			
		} else ErrExit(2);   /* Unplanned error because ArgCheck should have found it */
		
		while (fscanf(EntryFile, " ") == 1);   /* Advance Pointer until finding the next problem */
	}
	
/*********************************************** Exiting **************************************************************/

	fclose(OutputFile);   /* Close both files before exiting */
	fclose(EntryFile);
		
	return 0;   /* Exit Successfully */
}


