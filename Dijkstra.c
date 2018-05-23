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
/*static void printlist(AdjList j){
  while(j!=NULL){
    //printf("PRINTING LIST:%d has weight %d\n", j->w, j->weight);
    j= j->next;
  }
}*/
/*void addIntoList(PredNode* Head, PredNode* new){
  if (Head == NULL) {
    Head = new;
    return;
  } else {
    while(Head->next != NULL){
      Head = Head->next;
    }
    Head->next = new;
    return;
  } 
}
*/
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
  //showPQ(pq);
  //printf("___________");
  //set the dist value of src vertex to 0 so that it is extracted first
  ItemPQ new;
  new.key = v;
  new.value = 0;
  updatePQ(pq, new);
  //showPQ(pq);
  dist[v] = 0;
  //in the loop, PQ contains all the node with nodes with uninitialized shortest distance
  while(!PQEmpty(pq)){
    ItemPQ min = dequeuePQ(pq);
    isInPQ[min.key] = 0;
    int i = min.key; //store the key value
    //printf("\n\n\nFOR NODE %d\n", i);
    //Traverse through all adj vertices of i and update their distance values
    AdjList p = outIncident(g, i);//get all outgoing edges from graph
    //printlist(p);
    while (p!= NULL){
      int j = p->w; 
      //if shortest distance to j is not finalized yet, and distance to j through i is less than its previously calculated distance
      if(isInPQ[j]!=0 && dist[i]!=INT_MAX && p->weight + dist[i] < dist[j]){
        dist[j] = dist[i] + p->weight;//i->j
        //printf("dist[%d]%d = dist[%d]%d + [%d]%d\n", j,dist[j], i, dist[i], j, p->weight);
        PredNode* pred = (PredNode*)malloc(sizeof(PredNode));
        pred->v = i;
        pred->next = NULL;
        throwAway.pred[j] = pred;
        //addIntoList(throwAway.pred[j], pred);
        //update the distance value in PQ
        ItemPQ tmp;
        tmp.key = j;
        tmp.value = dist[j];
        //printf("ITEM KEY[%d], ITEM VALUE[%d]\n",j,dist[j]);
        updatePQ(pq, tmp);
        //showPQ(pq);
      }
      else if(isInPQ[j]!=0 && dist[i]!=INT_MAX && p->weight + dist[i] == dist[j]){
        dist[j] = dist[i] + p->weight;//i->j
        //printf("dist[%d]%d = dist[%d]%d + [%d]%d\n", j,dist[j], i, dist[i], j, p->weight);
        PredNode* pred = (PredNode*)malloc(sizeof(PredNode));
        pred->v = i;
        pred->next = NULL;
        PredNode* t = throwAway.pred[j];
        while (t->next!=NULL){
          t = t->next;
        }
        t->next = pred;
        //addIntoList(throwAway.pred[j], pred);
        //update the distance value in PQ
        ItemPQ tmp;
        tmp.key = j;
        tmp.value = dist[j];
        //printf("ITEM KEY[%d], ITEM VALUE[%d]\n",j,dist[j]);
        updatePQ(pq, tmp);
        //showPQ(pq);
      }
      p = p->next;
    }
  }
  for (int i =0; i<V; i++){
    if (dist[i] == INT_MAX) {
      dist[i] = 0;
    }
  }
  throwAway.dist = dist;
  freePQ(pq);
	return throwAway;
}


void showShortestPaths(ShortestPaths paths) {

}

void  freeShortestPaths(ShortestPaths paths) {

}



