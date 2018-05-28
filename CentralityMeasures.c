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
static int countReachableNodes(ShortestPaths sp, int v){
	int count = 0;
	for(int i=0; i<sp.noNodes; i++){
		if (sp.dist[i] != 0) {
			count++;
		}
	}
	count ++;
	return count;
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for (int i =0; i<throwAway.noNodes; i++){
		throwAway.values[i] = 0.000000;
	}
	for (int i =0; i<throwAway.noNodes; i++){
		ShortestPaths sp = dijkstra(g,i);
		double n = (double)countReachableNodes(sp, i);
		double N = (double)throwAway.noNodes;
		double sum = (double)(countPathSum((sp)));
		if (sum == 0) {throwAway.values[i] = 0; continue;}
		throwAway.values[i] = (n-1) * (n-1) / (N-1) / (sum);
		freeShortestPaths(sp);
	}
	return throwAway;
}

struct Queue{
	PredNode* Head;
};
typedef struct  Queue* Queue;

static void enqueue(Queue q, PredNode* n){
	if (q->Head == NULL) {
		q->Head = n;
		return;
	} 
	PredNode* tmp = q->Head;
	while (tmp->next!=NULL){
		tmp = tmp->next;
	}
	tmp ->next = n;
}

static PredNode* dequeue(Queue q){
	if (q->Head == NULL) return NULL;
	PredNode* tmp = q->Head;
	q->Head = tmp->next;
	return tmp;
}

static int emptyQ(Queue q){
	return (q->Head == NULL);
}
static int BFS(ShortestPaths sp, PredNode* n, int vertex){
	Queue q = malloc(sizeof(struct Queue));
	q->Head = NULL;
	int visited[sp.noNodes];
	for(int i =0; i<sp.noNodes; i++){
		visited[i] = 0;
	}
	enqueue(q,n);
	while(!emptyQ(q)){
		PredNode* curr = dequeue(q);
		visited[curr->v] = 1;
		while(curr!=NULL){
			if (curr->v == vertex) return 1;
			if (visited[sp.pred[curr->v]->v] == 0)
				enqueue(q,sp.pred[curr->v]);
			curr = curr->next;
		}
	}
	return 0;
}

static double countAppearances(ShortestPaths sp, int vertex){
	double sum = 0;
	for (int index = 0; index< sp.noNodes; index++){
		if (index==sp.src) continue;//does not count pred[src]
		PredNode* tmp = sp.pred[index];
		int count = 0;
		int identifer = 0;
		while (tmp!=NULL){
			count++;
			if (tmp->v == vertex) {
				identifer = 1;
			} else {
				PredNode* curr = sp.pred[tmp->v];
				/*while(curr!= NULL){
					if (curr->v == vertex){
						identifer=1;
						break;
					}
					else {
						curr = sp.pred[curr->v];
						}
					}
				}*/
				identifer = BFS(sp,curr, vertex);
			}
			tmp = tmp->next;
		}
		if (identifer == 1){
			sum += (double)1/(double)count;
		}
	}
	return sum;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for(int i=0; i<throwAway.noNodes; i++){
		throwAway.values[i] = 0;
	}
	for (int i =0; i<throwAway.noNodes; i++){
		for(int j= 0; j<throwAway.noNodes;j++){
			if (j==i) continue;
			ShortestPaths sp = dijkstra(g, i);
			throwAway.values[j] +=(double)(countAppearances(sp,j));
			freeShortestPaths(sp);
		}
	}
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = numVerticies(g);
	throwAway.values =  malloc(throwAway.noNodes*sizeof(double));
	for(int i=0; i<throwAway.noNodes; i++){
		throwAway.values[i] = 0;
	}
	for (int i =0; i<throwAway.noNodes; i++){
		for(int j= 0; j<throwAway.noNodes;j++){
			if (j==i) continue;
			ShortestPaths sp = dijkstra(g, i);
			throwAway.values[j] +=(double)(countAppearances(sp,j))/(double)(throwAway.noNodes-1)/(double)(throwAway.noNodes-2);
			freeShortestPaths(sp);
		}
	}
	return throwAway;
}

void showNodeValues(NodeValues values){
	for (int i =0; i<values.noNodes; i++){
		printf("%d: %f\n", i, values.values[i]);
	}
}

void freeNodeValues(NodeValues values){
	free(values.values);
}
