
#include "One.h"

void VControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	switch (ArgCheck(Arg)) {
		case 11:
			AOne(entryfp, outputfp, Arg);
			break;
		
		case 12:
			BOne(entryfp, outputfp, Arg);
			break;
		
		case 13:
			COne(entryfp, outputfp, Arg);
			break;
		
		case 14:
			DOne(entryfp, outputfp, Arg);
			break;
		default:
			Arg->err = 1;
			break;
	}
	
	free(Arg);
	return;
}

void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) { /* CLOSED */
	
	struct graph *g;
	double sum;
	
	g = VGRead(entryfp, Arg);                                                              /* Reading graph from file */
	sum = Kruskal(g, NULL, NoBin);                                     /* find the backbone using Kruskal´s Algorithm */

	/*EdgePrint(stdout, g->data, 0, Arg->v - 1);*/

	qsort(g->data, Arg->v - 1,               /* Sorting the backbone using the vertice criteria */
	      sizeof(struct edge*), lessVertice);
	
	if ((sum > 0) && (Arg->err == 0)) {                                      /* Print the graph, if there is no error */
		
		fprintf(outputfp, "%d %d %s %d %lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);                       /* Print error message */
	
	VGFree(g);                                                                            /* Free the graph */
	return;
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0;
	int *id = NULL, *sz = NULL, ncpos;
	
	UFinit(Arg->v, id, sz);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	G = VGRead(entryfp, Arg);
	
	sum = Kruskal(G, bindata, Bin); /*initial kruskal*/
	emptybin(bindata, ((struct edge **) G->data), G->Arg->v, G->Arg->e); /* Dump the bin onto the graph */
	
	if (SearchDelete(G, 0, G->Arg->v - 1, EdgeDelete) != 0) {
		find(G->Arg, ((struct edge **) G->data), id, sz); /* Restore Connectivity */
		emptybin(bindata, ((struct edge **) G->data), G->Arg->v, G->Arg->e);
		ncpos = binsearch(id,sz, G, G->Arg->v);
	}
	
	qsort(G->data, Arg->v - 1, sizeof(struct edge*), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,
		        flag);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		if (flag == 1)
			fprintf(outputfp, "%d %d %lf", ((struct edge **) G->data)[ncpos]->vi,
			        ((struct edge **) G->data)[ncpos]->vj, ((struct edge **) G->data)[ncpos]->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	VGFree(G);
	free(id);
	free(sz);
	
	return;
}


void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge **bindata;
	double sum[2] = {0,0};
	int *id = NULL, *sz = NULL, ncpos;
	fpos_t args, end;
	
	UFinit(Arg->v, id, sz);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	G = VGRead(entryfp, Arg);
	
	sum[0]=Kruskal(G, bindata, Bin); /*initial kruskal*/
	fgetpos(outputfp,&args);
	fprintf(outputfp,"\n");
	EdgePrint(outputfp, G->data, 0, Arg->v - 1);
	
	if ((ncpos=SearchDelete(G, 0, G->Arg->v - 1, EdgeDelete))!= 0) {
		
		EdgeSwitch(G->data,ncpos,G->Arg->e);
		G->Arg->e--;
		sum[1] = Kruskal(G,bindata,NoBin);
		G->Arg->e++;
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		fgetpos(outputfp,&end);
	}
	
	fsetpos(outputfp,&args);
	if (Arg->err == 0) fprintf(outputfp, "%d %d %s %d %lf %d %lf",Arg->v,Arg->e,Arg->var,Arg->v-1,sum[0],
							Arg->v-1,sum[1]);
	else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	fsetpos(outputfp,&end);
	VGFree(G);
	free(id);
	free(sz);
	
	return;
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0,PosSz, ncpos=0;
	int *id=NULL,*sz=NULL,count=0,*RelPos=NULL, i;
	
	G = VGRead(entryfp, Arg);
	bindata=CreateEdgeV(Arg->e-Arg->v+1);
	
	sum = Kruskal(G, bindata, Bin);
	emptybin(bindata, ((struct edge **) G->data), G->Arg->v, G->Arg->e);
	
	if ((PosSz=(SearchDelete(G, 0, G->Arg->v - 1, VerticeDelete))) != 0) {
		find(G->Arg, ((struct edge **) G->data), id, sz); /* Restore Connectivity */
		emptybin(bindata, ((struct edge **) G->data), G->Arg->v, G->Arg->e);
		
		
		if ((RelPos=(int *) malloc((PosSz-1)*sizeof(int)))==NULL) ErrExit(3);
		RelPos[0]=Arg->v;
		
		do
		{
			RelPos[count+1] = binsearch(id,sz, G,RelPos[count]);
			count++;
			/*Numero de arestas (no bin) que repõem a conectividade*/
		} while (count<PosSz);
	}
	
	/* Verify if every element in id[] has same root */	
	count = 0;
	PosSz = 0;

	for (i=0; i<Arg->e; i++)  /* Find 1st non error value for root*/
	{
		if (i!=RelPos[count])
		{
			PosSz = id[i];
			break;
		}
	}

	for	(i=0; i<Arg->e; i++)
	{
		if (i!=RelPos[count])
		{
			if (id[i] != PosSz)
			{
				PosSz = -1;
				break;
			}
		} else {
			count++;
		}
	}

	if (PosSz == -1)
	{
		Arg->err = 1;
	}

	qsort(G->data, Arg->v - 1, sizeof(struct edge*), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum,
			   	Arg->v - 1, flag);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		if (flag<0)fprintf(outputfp, "%d %d %lf", ((struct edge **) G->data)[ncpos]->vi,
		        ((struct edge **) G->data)[ncpos]->vj, ((struct edge **) G->data)[ncpos]->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	free(id);
	free(sz);
	VGFree(G);
	free(RelPos);
	
	return;	
}

void EOne(FILE* entryfp, FILE* outputfp, struct PBArg *Arg)
{
	return;
}

