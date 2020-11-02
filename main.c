#include "main.h"
#include "FileOp.h"

/********************************
 * Main Function of the program
 * @param argv Number of arguments read
 * @param argc Pointer to strings of arguments
 * @return
 ********************************/
 
int main(int argv, char **argc) {
	
	char *EntryFileName;
	FILE *EntryFile;
	
	strcpy(EntryFileName,argc[2]);
	
	EntryFile=FileOpen(EntryFileName); //Adicionar uma função que controle a abretura e leitura de tudo ? Tipo main do FileOp?
	
}
