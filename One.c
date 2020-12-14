
#include "One.h"
#include "Kruskal.h"

/***********************************************************************************************************************
 * Control of mode 1, which handles all modes that require the use of edge array as graph representation
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
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
	
	struct graph *g;   /* Graph in form of an array of edges */
	double sum = 0;   /* Total cost of the backbone */
	int StopMe;   /* Position where the backbone stops */
	
	g = VGRead(entryfp, Arg);   /* Read the graph from the input file */
	StopMe = Kruskal(g, &sum);   /* Apply kruskal´s Algorithm to get the backbone of the graph */
	
	
	/*fprintf(outputfp,"\n");*/
	if ((sum > 0) && (Arg->err == 0)) { /* Print backbone if no errors were detected during execution */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice); /* Sort the backbone in vertice order */
		fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, StopMe, sum);   /* Print Arguments */
		EdgePrint(outputfp, g->data, 0, StopMe);   /* Print the backbone */
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);    /* print error message */
	
	fprintf(outputfp, "\n");   /* At the end of output, a newline is printed */
	
	VGFree(g);   /* Free the allocated memory for the graph */
}

/***********************************************************************************************************************
 * Control of mode B1, which outputs the backbone without a predefined edge, resetting the connectivity
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;    /* Graph in form of an array of edges */
	double Sum = 0, NewSum = 0;   /* Total costs of the original backbone and the cost after resetting connectivity */
	int *id = NULL, *sz = NULL;   /* Auxiliary arrays for CWQU */
	int ncpos = 0, StopMe, NewStop, flag;   /* Auxiliary Variables */
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if (SearchDelete(g, 0, StopMe, EdgeDelete) != 0) {   /* If the deleted edge belongs to the backbone */
		
		if ((id = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		NewStop = CWQU(g->data, Arg->v, &NewSum, id, sz, StopMe);
		
		if (StopMe - NewStop > 1) {   /* Check if there is one edge replacing the deleted, or if more are necessary */
			flag = -1;
		} else {
			ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);
			if (ncpos >= 0) {/* Get the position of that edge */
				flag = 1;
			} else flag = -1;
		}
		SearchDelete(g, 0, StopMe, EdgeDelete);   /* Resetting the connectivity */
		
	} else if (SearchDelete(g, StopMe, Arg->e, EdgeDelete) != 0)
		flag = 0;   /* Deleted edge is on the graph but not on backbone*/
	else flag = -1;
	
	if (Arg->err == 0) {   /* If there were no errors, output the backbone. Else print error message */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);   /* Sort the backbone by Vertice criteria */
		fprintf(outputfp, "%d %d %s %d %d %d %.2lf %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, StopMe, Sum,
		        flag);
		EdgePrint(outputfp, g->data, 0, StopMe);   /* Print Arguments, and then print the backbone */
		if (flag == 1) {   /* If the deleted edge belonged to the backbone, print it */
			fprintf(outputfp, "%d %d %.2lf\n", g->data[ncpos]->vi, g->data[ncpos]->vj, g->data[ncpos]->cost);
		}
	} else {   /* if there´s an expected exception */
		fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	}
	fprintf(outputfp, "\n");   /* At the end of output, a newline is printed */
	VGFree(g);   /* Before exiting, free the graph and auxiliary arrays */
	free(id);   /* Free the auxiliary arrays */
	free(sz);
}

/***********************************************************************************************************************
 * Control of mode C1, which outputs the backbone both with and without a predefined edge
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g, *newg = NULL;   /* Graphs to store the original backbone & the backbone without the deleted edge */
	struct edge *temp;   /* Auxiliary edge for switches */
	double Sum = 0, NewSum = 0;   /* Total costs of the original backbone and the new backbone without the edge */
	int StopMe, NewStop = 0, ncpos = 0, i;   /* Auxiliary Variables */
	bool flag;   /* Boolean Auxiliary Flag */
	
	g = VGRead(entryfp, Arg);   /* Read the graph from input file */
	
	StopMe = Kruskal(g, &Sum);   /* Original kruskal */
	newg = graphcpy(g);   /* Make a copy of the sorted graph */
	
	if (SearchDelete(g, 0, StopMe, EdgeDelete) != 0) {   /* If the edge belongs to the backbone */
		for (i = 0; i < StopMe; i++) {   /* Get the position of that edge */
			if (g->data[i]->cost < 0) ncpos = i;
		}
		
		temp = newg->data[ncpos];   /* Change that edge to the last position */
		newg->data[ncpos] = newg->data[g->Arg->e - 1];
		newg->data[g->Arg->e - 1] = temp;
		
		newg->Arg->e--;
		NewStop = Kruskal(newg, &NewSum);   /* Do Kruskal´s Algorithm again, without that edge */
		newg->Arg->e++;
		
		flag = 1;   /* Set the flag to True */
	} else {
		flag = 0;   /* Deleted edge is on the graph but not on backbone*/
	}
	
	if ((Arg->err == 0) && (flag == 1)) {   /* Print when edge is deleted */
		
		fprintf(outputfp, "%d %d %s %d %d %d %.2lf %d %.2lf\n",
		        Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, StopMe, Sum, NewStop, NewSum);
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		qsort(newg->data, NewStop, sizeof(struct edge *), lessVertice);
		
		SearchDelete(g, 0, StopMe, EdgeDelete);
		SearchDelete(newg, 0, NewStop, EdgeDelete);
		
		EdgePrint(outputfp, g->data, 0, StopMe);
		EdgePrint(outputfp, newg->data, 0, NewStop);
		
	} else if ((Arg->err == 0) && (flag == 0)) {   /* Print when edged isn´t necessary for the original backbone */
		
		fprintf(outputfp, "%d %d %s %d %d %d %.2lf -1\n",
		        Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, StopMe, Sum);
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		
		SearchDelete(g, 0, StopMe, EdgeDelete);
		
		EdgePrint(outputfp, g->data, 0, StopMe);
		
	} else fprintf(outputfp, "%d %d %s %d -1\n",Arg->v, Arg->e, Arg->var, Arg->vi);   /* Expected exception */
	
	fprintf(outputfp, "\n");   /* At the end of output, a newline is printed */
	VGFree(g);   /* Free all dynamically allocated memory */
	free(newg->data);
	free(newg);
}

/***********************************************************************************************************************
 * Function to control mode D1, which outputs the backbone when a vertice is deleted
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	struct edge** backup;
	double Sum = 0, NewSum=0;
	int *id = NULL, *sz = NULL, *del=NULL, delcnt, StopMe, i;
	int cnt = 0;
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if ( (delcnt = SearchDelete(g, 0, StopMe, VerticeDelete)) >= 1) {
		/* If the deleted edge belongs to the backbone */
		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		if ((id = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((del = (int *) malloc( (delcnt + 1) * sizeof(int))) == NULL) ErrExit(3);
		/* In this version, the algorithm is divided so it can output different information */
		CWQU(g->data, Arg->v, &NewSum, id, sz, StopMe);
		del[0]=StopMe;
		SearchDelete(g, StopMe, g->Arg->e, VerticeDelete);
		
		for (i=0; i < delcnt; i++){
			
			del[i+1] = N_binsearch(g->data, id, sz, del[i], g->Arg->e);   /* Get the position of that edge */
			if (del[i + 1] != -1) cnt++;   /* If there isn´t anymore unions to be made */
			else break;
		}
	} else cnt = -1; /* If the vertice doesn´t belong to the graph */
	
	if (cnt>=1)   /* Sort edges that reset the connectivity */
	{
		backup = CreateEdgeV(cnt);
		
		for (i=1; i <= cnt; i++) backup[i-1] = g->data[ del[i] ];
		qsort(backup, cnt, sizeof(struct edge *), lessVertice);
		
	} else backup = NULL;
	
	if (Arg->err == 0){
		
		SearchDelete(g, 0, StopMe, VerticeDelete);
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);   /* Sort edges by vertice criteria */
		
		fprintf(outputfp, "%d %d %s %d %d %.2lf %d\n",Arg->v, Arg->e, Arg->var, Arg->vi, StopMe, Sum, cnt);
		EdgePrint(outputfp, g->data, 0, StopMe);   /* Print Arguments, backbone and backup edges */
		EdgePrint(outputfp, backup, 0, cnt);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	fprintf(outputfp,"\n");   /* At the end of output, a newline is printed */
	VGFree(g);   /* Free all dynamically allocated memory */
	free(id);
	free(sz);
	free(del);
}


/***********************************************************************************************************************
 * Function to control mode E1, which outputs the backbone and it´s backup
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void EOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	struct graph *g;   /* Graph stored as an array of edges */
	struct edge **backup;   /* Backup array of edges  */
	double NewSum = 0, Sum = 0;    /* Total costs of the original backbone and the cost after resetting connectivity */
	int i, *id, *sz, StopMe;   /* Auxiliary Variables */
	
	g = VGRead(entryfp, Arg);   /* Read the graph */
	StopMe = Kruskal(g, &Sum);   /* Initial Kruskal´s Algorithm */
	
	backup = CreateEdgeV(StopMe);   /* Allocate memory for the backup */
	if ((id = malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);   /* Allocate memory for the CWQU arrays */
	if ((sz = malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
	
	fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, StopMe, Sum);   /* Print Arguments */
	
	qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);   /* Sort the backbone by vertice criteria */
	
	for (i = 0; i < StopMe; i++) {
		NewSum = 0;   /* Setting NewSum for current edge */
		g->data[i]->cost = -g->data[i]->cost;   /* "Marking" current edge as unusable */
		backup[i] = ProblemSolver(g, &NewSum, StopMe);   /* Getting the backup */
		g->data[i]->cost = -g->data[i]->cost;   /* "Unmarking" edge */
		/* Print backbone edge */
		fprintf(outputfp, "%d %d %.2lf ",g->data[i]->vi, g->data[i]->vj, g->data[i]->cost);
		if (backup[i] == NULL) {    /* Print no backup possible */
			fprintf(outputfp, "-1\n");
		} else {   /* Print corresponding backup edge  */
			fprintf(outputfp, "%d %d %.2lf\n",backup[i]->vi, backup[i]->vj, backup[i]->cost);
		}
	}
	fprintf(outputfp, "\n");   /* At the end of output, a newline is printed */
	VGFree(g);   /* Free all dynamically allocated memory */
	FreeEdgeV(backup, StopMe);
	free(id);
	free(sz);
}



