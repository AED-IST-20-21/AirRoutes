//
// Created by anton on 11/30/2020.
//

struct graph* GraphInit(){
	struct graph *G;
	
	if ((G = (struct graph *) malloc(sizeof(struct graph)))==NULL)
		ErrExit(3);
	
	return G;
}

/**********************
 * Memory allocation and Initialization of PBArg
 * @return clean PBArg
 *********************/
 
struct PBArg *PBinit(){
	
	struct PBArg *aux;
	
	if ((aux = (struct PBArg* ) malloc(sizeof(struct PBArg)))==NULL)
		ErrExit(3);
	
	aux->v = 0;
	aux->e = 0;
	aux->vi = 0;
	aux->vj = 0;
	aux->var[0] = '\0';
	aux->err =0;
	
	return aux;
}




