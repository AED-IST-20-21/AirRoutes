
#include "One.h"
#include "Kruskal.h"

/***********************************************************************************************************************
 * Control of mode 1, which handles all modes that require the use of edge vector as graph representation
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
		} else fprintf(outputfp,"\n");
		
	} else {
		fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	}
	
	VGFree(g); /* Before exiting, free the graph and auxiliary vectors */
	free(id);
	free(sz);
}

void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g, *newg=NULL;
	struct edge* temp;
	double Sum=0, NewSum=0;
	int StopMe=0, NewStop=0, ncpos=0, i;
	int *id = NULL, *sz = NULL;
	bool flag=0;
	
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

		temp = g->data[ncpos];
		g->data[ncpos] = g->data[g->Arg->e - 1];
		g->data[g->Arg->e - 1] = temp;

		g->Arg->e--;
		NewStop = Kruskal(newg, &NewSum);
		g->Arg->e++;

	} else {
		/* Imprimir com 0 */
	}

	if (StopMe - NewStop != 0)
	{
		flag = 1;
	}

#if 0	
	if (NewStop < Arg->v) {
		
		if ((newid = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((newsz = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		
		vectorcpy(newid, id);
		vectorcpy(newsz, sz);
		
		
		StopMe = CWQU(g->data, Arg->v, &Sum, id, sz, Arg->e);
		
		newg->data[NewStop]->cost = -newg->data[NewStop]->cost;
		EdgeBreak(g->data, Arg->e, newid);
		
		NewStop = CWQU(newg, &NewSum, newid, newsz, Arg->e);
		
		newg->data[NewStop]->cost = -newg->data[NewStop]->cost;
		
	} else flag = 1;
#endif
	if ((Arg->err == 0) && (flag == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %lf %d %lf\n", 
				Arg->v, Arg->e, Arg->var, StopMe, Sum, NewStop, NewSum);

		EdgePrint(outputfp, g->data, 0, StopMe);
		EdgePrint(outputfp, newg->data, 0, NewStop);
		
	} else if ((Arg->err == 0) && (flag == 1)) {
		
		fprintf(outputfp, "%d %d %s %d %lf -1\n", Arg->v, Arg->e, Arg->var, StopMe, Sum);
		EdgePrint(outputfp, g->data, 0, g->Arg->v);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);
	
	
	
	VGFree(g);
	free(newg->data);
	free(newg);
	free(id);
	free(sz);
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	double Sum = 0, NewSum=0;
	int *id = NULL, *sz = NULL, *del=NULL, delcnt=0, StopMe=0, i;
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if ((delcnt=SearchDelete(g, 0, StopMe, VerticeDelete) != 0)) {   /* If the deleted edge belongs to the backbone */
		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		if ((id = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((del = (int *) malloc( delcnt * sizeof(int))) == NULL) ErrExit(3);
		/* In this version, the algorithm is divided so it can output different information */
		CWQU(g->data, Arg->v, &NewSum, id, sz, StopMe);
		del[0]=StopMe;

		for (i=0; i < delcnt-1; i++){
			/*del[i] =CWQU(g->data, Arg->v, &NewSum, id, sz,del[i]);*/
			del[i+1] = binsearch(g->data, id, sz, del[i], g->Arg->e);   /* Get the position of that edge */
			if (del[i+1] != -1)
			{
				Arg->err = 1;
				break;
			}
			g->data[del[i]]->cost=-g->data[del[i]]->cost;
		}
	}
	
	if (Arg->err == 0) {
		fprintf(outputfp, "%d %d %s %d %.2lf %d\n", Arg->v, Arg->e, Arg->var, StopMe,Sum,delcnt);
		EdgePrint(outputfp, g->data, 0, StopMe);
		
		for (i=0; i < delcnt; i++)
		{
			fprintf(outputfp, "%d %d %lf\n", g->data[del[i]]->vi,
					g->data[del[i]]->vj, g->data[del[i]]->cost);
		}
	
	} else fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	free(id);
	free(sz);
	free(del);
	VGFree(g);
	

}

void EOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	struct graph *g;
	struct edge** backup;
	double KSum, NewSum, *Sum;
	int i,*id,*sz;
	int StopMe;
	
	g=VGRead(entryfp,Arg);
	StopMe = Kruskal(g, &KSum);

	backup = CreateEdgeV(Arg->v);
	if ((Sum = (double*) malloc(Arg->v * sizeof(double)))==NULL) ErrExit(3);
	/*
	if ((backup = malloc(Arg->v * sizeof(int)))==NULL) ErrExit(3);
	*/
	if ((id=malloc(Arg->v * sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(Arg->v * sizeof(int)))==NULL) ErrExit(3);
	
	for(i = 0; i < StopMe; i++)
	{
		NewSum = 0;

		/*EdgeDelete*/
		g->data[i]->cost = -g->data[i]->cost;

		/*Find Replacement Edge*/
		backup[i] = ProblemSolver(g, &NewSum, StopMe);
		Sum[i] = NewSum;

		/*EdgeRestore*/
		g->data[i]->cost = -g->data[i]->cost;
	}
		
	/*EOnePrint(outputfp, g, Sum, backup);*/
	free(id);
	free(sz);
	VGFree(g);
	free(g->data);
	free(g);
	
	return;
}

struct edge* ProblemSolver(struct graph* g, double* Sum, int StopMe)
{
	struct edge* backup;
	int NewStop, ncpos, *id, *sz;

	if ((id=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);

	NewStop = CWQU(g->data, g->Arg->v, Sum, id, sz, StopMe);

	if (StopMe - NewStop > 1)
	{
		free(id);
		free(sz);
		return NULL;
	}
	
	ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);

	if (ncpos ==-1)
	{
		free(id);
		free(sz);
		return NULL;
	}

	backup = g->data[ncpos];
	
	free(id);
	free(sz);
	return backup;
}
