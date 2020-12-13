
#include "One.h"
#include "Kruskal.h"

/***********************************************************************************************************************
 * Control of mode 1, which handles all modes that require the use of edge array as graph representation
 * @param entryfp Input File
 * @param outputfp Output File
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void VControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	switch (ArgCheck(Arg)) {   /* Converts Arguments to an integer and switches it */
		case 11:
			AOne(entryfp, outputfp, Arg);   /*Standard Backbone*/
			break;
		case 12:
			BOne(entryfp, outputfp, Arg);   /* Variational Backbone with 1 edge deleted */
			break;
		case 13:
			COne(entryfp, outputfp, Arg);   /* Non-Variational backbone with 1 edge deleted  */
			break;
		case 14:
			DOne(entryfp, outputfp, Arg);   /* Variational backbone with 1 vertice deleted */
			break;
		case 15:
			EOne(entryfp, outputfp, Arg);   /* backbone and backup for each edge */
			break;
		default:
			Arg->err = 1;   /* if no mode is selected, there is an error */
			break;
	}
	
	free(Arg);   /*Free the allocated memory for the problem arguments */
}

/***********************************************************************************************************************
 * Control of Mode A1, which prints the outputs backbone
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) { /*IS WORKING*/
	
	struct graph *g;
	double sum = 0;   /* Total cost of the backbone */
	int StopMe;   /* Position where the backbone stops */
	
	g = VGRead(entryfp, Arg);   /* Read the graph from the input file */
	StopMe = Kruskal(g, &sum);   /* Apply kruskal´s Algorithm to get the backbone of the graph */
	
	
	/*fprintf(outputfp,"\n");*/
	if ((sum > 0) && (Arg->err == 0)) { /* Print backbone if no errors were detected during execution */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice); /* Sort the backbone in vertice order */
		fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, StopMe, sum);
		EdgePrint(outputfp, g->data, 0, StopMe);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);    /* print error message */
	
	fprintf(outputfp,"\n");
	
	VGFree(g);   /* Free the allocated memory for the graph */
}

/***********************************************************************************************************************
 * Control of mode B1, which outputs the backbone without a predefined edge
 * @param entryfp Input File
 * @param outputfp Output File
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	double Sum = 0, NewSum=0;
	int *id = NULL, *sz = NULL, ncpos=0, StopMe=0, NewStop=0,flag=-5;
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if (SearchDelete(g, 0, StopMe, EdgeDelete) != 0) {   /* If the deleted edge belongs to the backbone */
		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		if ((id = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		/* In this version, the algorithm is divided so it can output different information */
		NewStop = CWQU(g->data, Arg->v, &NewSum, id, sz, StopMe);
		
		if (StopMe - NewStop > 1) {   /* Check if there is one edge replacing the deleted, or if more are necessary */
			flag=-1;
		} else {
			ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);
			if (ncpos>=0){/* Get the position of that edge */
				flag=1;
			} else flag=-1;
		}
		SearchDelete(g, 0, StopMe, EdgeDelete);
		
	} else if (SearchDelete(g,StopMe,Arg->e,EdgeDelete)!=0) flag=0;
	else flag =-1;
	
	if (Arg->err == 0) {   /* If there were no errors, output the backbone. Else print error message */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		fprintf(outputfp,"%d %d %s %d %d %d %.2lf %d\n",Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj,StopMe, Sum, flag);
		EdgePrint(outputfp, g->data, 0, StopMe);
		if (flag==1) {
			fprintf(outputfp, "%d %d %.2lf\n", g->data[ncpos]->vi, g->data[ncpos]->vj, g->data[ncpos]->cost);
		}
		
	} else {
		fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	}
	fprintf(outputfp,"\n");
	VGFree(g); /* Before exiting, free the graph and auxiliary arrays */
	free(id);
	free(sz);
}

void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g, *newg=NULL;
	struct edge* temp;
	double Sum=0, NewSum=0;
	int StopMe=0, NewStop=0, ncpos=0, i;
	int *id = NULL, *sz = NULL;
	bool flag=1;
	
	g = VGRead(entryfp, Arg);
	
	if ((id = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
	if ((sz = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
	
	StopMe = Kruskal(g, &Sum);
	newg = graphcpy(g);
		
	if ( SearchDelete(g, 0, StopMe, EdgeDelete) != 0)
	{
		for (i=0; i<StopMe; i++)
		{
			if (g->data[i]->cost < 0)
			{
				ncpos = i;
			}
		}

		temp = newg->data[ncpos];
		newg->data[ncpos] = newg->data[g->Arg->e - 1];
		newg->data[g->Arg->e - 1] = temp;

		newg->Arg->e--;
		NewStop = Kruskal(newg, &NewSum);
		newg->Arg->e++;
		
		flag = 1;

	} else if (SearchDelete(g, StopMe, g->Arg->e, EdgeDelete)!=0)
	{	/* Aresta não está nem na mst nem no bin */
		flag = 0;
	} else {
		flag = 0;
	}

	if ((Arg->err == 0) && (flag == 1)) {
		
		fprintf(outputfp, "%d %d %s %d %d %d %.2lf %d %.2lf\n", 
				Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, StopMe, Sum, NewStop, NewSum);
	
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		qsort(newg->data, NewStop, sizeof(struct edge *), lessVertice);

		SearchDelete(g, 0, StopMe, EdgeDelete);
		SearchDelete(newg, 0, NewStop, EdgeDelete);

		EdgePrint(outputfp, g->data, 0, StopMe);
		EdgePrint(outputfp, newg->data, 0, NewStop);
		
	} else if ((Arg->err == 0) && (flag == 0)) {
	
		fprintf(outputfp, "%d %d %s %d %d %d %.2lf -1\n",
			   	Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, StopMe, Sum);	
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		
		SearchDelete(g, 0, StopMe, EdgeDelete);

		EdgePrint(outputfp, g->data, 0, StopMe);
		
	} else fprintf(outputfp, "%d %d %s %d -1\n", 
			Arg->v, Arg->e, Arg->var, Arg->vi);
	
	fprintf(outputfp,"\n");
	VGFree(g);
	free(newg->data);
	free(newg);
	free(id);
	free(sz);
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	struct edge** backup;
	/*void *a, *b;*/
	double Sum = 0, NewSum=0;
	int *id = NULL, *sz = NULL, *del=NULL, delcnt=0, StopMe=0, i;
	int cnt = 0;
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if ( (delcnt = SearchDelete(g, 0, StopMe, VerticeDelete)) >= 1) {   /* If the deleted edge belongs to the backbone */
/*		
		size = delcnt;
		if (delcnt==1) delcnt++;
*/

		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		if ((id = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((del = (int *) malloc( (delcnt + 1) * sizeof(int))) == NULL) ErrExit(3);
		/* In this version, the algorithm is divided so it can output different information */
		CWQU(g->data, Arg->v, &NewSum, id, sz, StopMe);
		
		del[0]=StopMe;
		
		SearchDelete(g, StopMe, g->Arg->e, VerticeDelete);

		for (i=0; i < delcnt; i++){
			/*del[i] =CWQU(g->data, Arg->v, &NewSum, id, sz,del[i]);*/
			del[i+1] = N_binsearch(g->data, id, sz, del[i], g->Arg->e);   /* Get the position of that edge */

			if (del[i+1] == -1)
			{
				/*delcnt = 0;*/ /*Conectividade não foi reposta*/
				break;
			} else {
				/*g->data[ del[i+1] ]->cost=-g->data[ del[i+1] ]->cost;*/
				cnt++;
			}

		}
		
	} else {
		delcnt = -1; /*vertice não pertence ao grafo*/
		cnt = -1;
	}

	/* Organizar por vértice as arestas q repõem a conectividade */

	if (cnt>=1)
	{
		backup = CreateEdgeV(cnt);	

		for (i=1; i <= cnt; i++)
		{
			backup[i-1] = g->data[ del[i] ];
		}
		qsort(backup, cnt, sizeof(struct edge *), lessVertice);
	} else {
		backup = NULL;
	}

	if (Arg->err == 0) 
	{
		/*Volta a colocar custos positivos*/
		SearchDelete(g, 0, StopMe, VerticeDelete);
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
	
		fprintf(outputfp, "%d %d %s %d %d %.2lf %d\n", 
				Arg->v, Arg->e, Arg->var, Arg->vi, StopMe, Sum, cnt);

		EdgePrint(outputfp, g->data, 0, StopMe);
			
		EdgePrint(outputfp, backup, 0, cnt);
	
	} else fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	fprintf(outputfp,"\n");
	free(id);
	free(sz);
	free(del);
	VGFree(g);
	

}

void EOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	struct graph *g;
	struct edge** backup;
	double NewSum = 0, Sum = 0;
	int i,*id,*sz;
	int StopMe;
	
	g = VGRead(entryfp,Arg);
	StopMe = Kruskal(g, &Sum);

	backup = CreateEdgeV(StopMe);
	if ((id=malloc(Arg->v * sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(Arg->v * sizeof(int)))==NULL) ErrExit(3);

	
	fprintf(outputfp, "%d %d %s %d %.2lf\n",Arg->v, Arg->e, Arg->var, StopMe, Sum);
	
	qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);

	for(i = 0; i < StopMe; i++)
	{
		NewSum = 0;

		/*EdgeDelete*/
		g->data[i]->cost = -g->data[i]->cost;

		/*Find Replacement Edge*/
		backup[i] = ProblemSolver(g, &NewSum, StopMe);

		/*EdgeRestore*/
		g->data[i]->cost = -g->data[i]->cost;

		fprintf(outputfp, "%d %d %.2lf ",
			   	g->data[i]->vi, g->data[i]->vj, g->data[i]->cost);
		if (backup[i] == NULL)
		{
			fprintf(outputfp, "-1\n");
		} else {
			fprintf(outputfp, "%d %d %.2lf\n",
				   	backup[i]->vi, backup[i]->vj, backup[i]->cost);
		}
	}
	fprintf(outputfp,"\n");
	
	FreeEdgeV(backup,StopMe);
	free(id);
	free(sz);
	VGFree(g);
	
	return;
}



