// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

/*
typedef struct NodeValues {
   int noNodes;
   double* values;
} NodeValues;
*/
static int countListItems(AdjList list){
	int count = 0;
	while (list != NULL){
		count++;
		list = list -> next;
	}
	return count;
}

NodeValues outDegreeCentrality(Graph g){//number of outward edges from this vertice
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for (int i =0; i<throwAway.noNodes; i++){
		AdjList list = outIncident(g,i);
		throwAway.values[i] = (double)countListItems(list);
	}
	return throwAway;
}
NodeValues inDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for (int i =0; i<throwAway.noNodes; i++){
		AdjList list = inIncident(g,i);
		throwAway.values[i] = (double)countListItems(list);
	}
	return throwAway;
}
NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for (int i =0; i<throwAway.noNodes; i++){
		AdjList listin = inIncident(g,i);
		AdjList listout = outIncident(g,i);
		throwAway.values[i] = ((double)countListItems(listin)+(double)countListItems(listout));
	}
	return throwAway;
}

static int countPathSum(ShortestPaths sp){
	int sum  =0;
	for (int i=0; i< sp.noNodes; i++){
		sum+=sp.dist[i];
	}
	return sum;
}
NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for (int i =0; i<throwAway.noNodes; i++){
		throwAway.values[i] = (double)(throwAway.noNodes-1)/(double)(countPathSum((dijkstra(g, i))));
	}
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
	for (int i =0; i<values.noNodes; i++){
		printf("%d: %f\n", i, values.values[i]);
	}
}

void freeNodeValues(NodeValues values){

}
