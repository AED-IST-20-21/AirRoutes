#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Zero.h"
#include "One.h"
#include "Graph.h"
#include "FileOp.h"

/***********************************************************************************************************************
 * Main Function of the Program Backbones
 * @param argc Number of Arguments passed from the Terminal
 * @param argv Vector of strings containing each argument passed from the Terminal
 * @return 0 if successful operation
 **********************************************************************************************************************/
int main(int argc, char *argv[]) {
	
	char *EntryFileName = NULL, *OutputFileName = NULL;                                                 /* File Names */
	FILE *EntryFile, *OutputFile;                                                                    /* File Pointers */
	struct PBArg *Arg;                                                                   /* Current Problem Arguments */
	
	if (argc != 2) return 0;                         /* Exit program if number of arguments is different than desired */

/********************************************* Initialization *********************************************************/

	EntryFileName = (char*) malloc((strlen(argv[1]) + 1) * sizeof(char));

	strcpy(EntryFileName,argv[1]);                                                         /* Store Entry file´s name */
	OutputFileName = ExitFileName(EntryFileName);                                          /* Create exit file´s name */
	EntryFile = RFileOpen(EntryFileName);                                                          /* Open Input File */
	OutputFile = WFileOpen(OutputFileName);                                                       /* Open Output File */
	free(OutputFileName);                                 /* Once the output file is open, it´s name can be discarded */
	free(EntryFileName);
	
/********************************************* Problem Solving ********************************************************/
	
	while (!feof(EntryFile)) {                           /* While End of File isn´t reached, work on the next problem */
		
		if ((Arg = ArgRead(EntryFile)) == NULL) {/*TODO*/
		
		}
		
		if (Arg->var[1] == '0') {                              /* If problem from mode 0, resolve with adjacency list */
			
			LControl(EntryFile, OutputFile, Arg);
			
		} else if (Arg->var[1] ==
		           '1') {                           /* If problem from mode 1, resolve with edge vector */
			
			VControl(EntryFile, OutputFile, Arg);
			
		} else ErrExit(2);                          /*   If Problem is neither from mode 0 nor mode 1, exit with an
													* unplanned error, because it should have been noticed in ArgRead */
		while (fscanf(EntryFile, " ") == 1);                         /* Advance Pointer until finding another problem */
	}
	
/*********************************************** Exiting **************************************************************/

		fclose(OutputFile);                                                        /* Close both files before exiting */
		fclose(EntryFile);
		
		return 0;                                                                                /* Exit Successfully */
}


