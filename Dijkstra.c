// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
/*typedef struct PredNode {
   int         v;
   struct PredNode *next;
} PredNode;

typedef struct ShortestPaths {
   int noNodes;
   int src;
   int *dist;
   PredNode **pred;
} ShortestPaths;*/

//calculate distance from src to all vertices. 
//
ShortestPaths dijkstra(Graph g, Vertex v) {
	ShortestPaths throwAway;
  throwAway.src = v;
  int V = numVerticies(g);
  throwAway.noNodes = V;
  throwAway.pred = malloc(V*(sizeof(PredNode*)));
  
  //set all pred values to NULL
  for (int c =0; c<V; c++){
    throwAway.pred[c]= NULL;
  }
  int dist[V];
  int isInPQ[V];
  PQ pq = newPQ();
  //initiate the piority queue with all the vertices.
  for (int i=0; i<V; i++){
    dist[i] = INT_MAX;
    ItemPQ new;
    new.key = i;
    new.value = dist[i];
    addPQ(pq, new);
    isInPQ[i] = 1;
  } 
  //set the dist value of src vertex to 0 so that it is extracted first
  ItemPQ new;
  new.key = v;
  new.value = 0;
  updatePQ(pq, new);
  //in the loop, PQ contains all the node with nodes with uninitialized shortest distance
  while(!PQEmpty(pq)){
    ItemPQ min = dequeuePQ(pq);
    isInPQ[min.key] = 0;
    int i = min.key; //store the key value
    //Traverse through all adj vertices of i and update their distance values
    AdjList p = outIncident(g, i);//get all outgoing edges from graph
    while (p!= NULL){
      int j = p->w;
      //if shortest distance to j is not finalized yet, and distance to j through i is less than its previously calculated distance
      if(isInPQ[j]!=0 && dist[i]!=INT_MAX && p->weight + dist[i] < dist[j]){
        dist[j] = dist[i] + p->weight;//i->j
        PredNode* pred = (PredNode*)malloc(sizeof(PredNode));
        pred->v = i;
        pred->next = throwAway.pred[j];
        throwAway.pred[j] = pred;
        //update the distance value in PQ
        ItemPQ tmp;
        tmp.key = j;
        tmp.value = dist[j];
        updatePQ(pq, tmp);
      }
      p = p->next;
    }
  }
  throwAway.dist = dist;
	return throwAway;
}


void showShortestPaths(ShortestPaths paths) {

}

void  freeShortestPaths(ShortestPaths paths) {

}



