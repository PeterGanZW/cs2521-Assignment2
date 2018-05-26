// Graph ADT interface for Ass2 (COMP2521)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

struct GraphRep{
    int noNodes;
    int noEdges;
    struct _adjListNode** List;
};

void addNode (AdjList list, int i, int weight);
// vertices are ints

Graph newGraph(int noNodes){
    Graph graph = malloc(sizeof(struct GraphRep));
    graph -> noNodes = noNodes;
    graph -> noEdges = 0;
    graph -> List = malloc((noNodes)*sizeof(adjListNode*));

    for(int i =0; i<noNodes; i++){
        graph->List[i] = NULL;
    }
    return graph;
}

adjListNode* newNode(int v, int weight, adjListNode* next){
    adjListNode* new = malloc(sizeof(adjListNode));
    new->w = v;
    new->next = next;
    new->weight = weight;
    return new;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight){
    //Add edge from src to dest
    adjListNode* new = newNode(dest,weight,NULL);
    new->next = g->List[src];
    g->List[src] = new;
    g->noEdges++;
}
void  removeEdge(Graph g, Vertex src, Vertex dest){
    adjListNode* curr = g->List[src];
    adjListNode* prev = curr;
    if (curr->w == dest){
        g->List[src] = curr->next;
        g->noEdges--;
        return;
    }
    while(curr!=NULL){
        if (curr->w == dest){
            prev->next = curr->next;
            curr = NULL;
            break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    g->noEdges--;
}
bool adjacent(Graph g, Vertex src, Vertex dest){
    assert(g!=NULL);
    adjListNode* curr = g->List[src];
    while(curr!= NULL){
        if (curr->w == dest) return true;
        else curr = curr->next;
    }
    return false;
}

int  numVerticies(Graph g){
    return g->noNodes;
}

/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
**/
AdjList outIncident(Graph g, Vertex v){
    if (g->List[v] == NULL) return NULL;
    adjListNode* curr = g->List[v];
    adjListNode* newlist = newNode(curr->w,curr->weight,NULL); 
    while(curr->next!= NULL){
        adjListNode* new = newNode(curr->next->w,curr->next->weight,NULL);
        new -> next = newlist;
        newlist = new;
        curr = curr->next;
    }
    return newlist;
}
/*

 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/
AdjList inIncident(Graph g, Vertex v){
    adjListNode* newlist = newNode(-1, -1, NULL); 
    for (int i =0; i< v; i++){
        adjListNode* curr = g->List[i];
        while(curr!= NULL){
            if (curr->w == v){
                addNode(newlist,i,curr->weight);
            }
            curr = curr-> next;
        }
    }
    for(int i = v+1; i<g->noNodes; i++){
        adjListNode* curr = g->List[i];
        while(curr!= NULL){
            if (curr->w == v){
                addNode(newlist,i,curr->weight);
            }
            curr = curr-> next;
        }
    }
    if (newlist->w == -1) return NULL;
    return newlist;
}

void addNode (AdjList list, int i, int weight){
    if (list->w == -1){
        list -> w = i;
        list -> weight = weight;
        return;
    } 
    adjListNode* new = newNode(i,weight, NULL);
    adjListNode* next = list-> next;
    new -> next = next;
    list -> next = new;
}

void  showGraph(Graph g){
    assert(g!= NULL);
    printf("#vertices=%d, #edges=%d\n\n",numVerticies(g),g->noEdges);
    for(int i =0; i<g->noNodes; i++){
        adjListNode* curr = g->List[i];
        printf("%d ----->", i);
        while (curr != NULL){
            printf("%d",curr->w);
            printf("(weight:%d)",curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}
void  freeGraph(Graph g){
    for(int i=0; i<g->noNodes;i++){
        adjListNode* curr = g->List[i];
        while (curr!= NULL){
            adjListNode* prev = curr;
            curr = curr-> next;
            free(prev);
        }
    }
    free(g);
}
