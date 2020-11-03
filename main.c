#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "FileOp.h"

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argv, char **argc)
{
	
	char *EntryFileName = "\0";
	//FILE *EntryFile;
	
	strcpy(EntryFileName,argc[2]);
	
//EntryFile = FileOpen(EntryFileName); //Adicionar uma função que controle a abretura e leitura de tudo ? Tipo main do FileOp?
return 0;	
}
