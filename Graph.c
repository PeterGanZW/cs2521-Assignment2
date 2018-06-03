// Graph ADT interface for Ass2 (COMP2521)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

struct GraphRep{                 // struct of GraphRep involves:
    int noNodes;                 // number of nodes
    int noEdges;                 // number of edges
    struct _adjListNode** List;  // Adjacency List
};

void addNode (AdjList list, int i, int weight);
// vertices are ints

Graph newGraph(int noNodes){
    Graph graph = malloc(sizeof(struct GraphRep));          // malloc memory for graph
    graph -> noNodes = noNodes;                             // set #nodes with the given vertex
    graph -> noEdges = 0;                                   // set #edges to 0
    graph -> List = malloc((noNodes)*sizeof(adjListNode*)); // malloc memory for Adjacency list
    int i;
    for(i =0; i<noNodes; i++){                          // set all the node pointer in the list to be NULL
        graph->List[i] = NULL;
    }
    return graph;                                           // return the new graph
}

adjListNode* newNode(int v, int weight){
    adjListNode* new = malloc(sizeof(adjListNode));  // malloc memory for new node
    new->w = v;                                      // set new->w to be the given v
    new->next = NULL;                                // set next node to be NULL
    new->weight = weight;                            // set new->weight to be the given weight
    return new;                                      // return the new node
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight){
    //Add edge from src to dest
    adjListNode* new = newNode(dest,weight);         // create a new node
    new->next = g->List[src];                        // set the new node to be the first node in the list[src]
    g->List[src] = new;                              // joint previous list[src] to be the next node of new list[src]
    g->noEdges++;                                    // #edges + 1
}

void  removeEdge(Graph g, Vertex src, Vertex dest){
    adjListNode* curr = g->List[src];                // recode the list[src] in curr
    adjListNode* prev = curr;                        // prev represent the node which before the curr node
    if (curr->w == dest){                            // if the first node is the destination
        g->List[src] = curr->next;                   // list[src] move ot the next node
        g->noEdges--;                                // #edges - 1
        return;                                      // end function
    }
    while(curr!=NULL){                               // if destination is not the first node
        if (curr->w == dest){                        // check every node in the list one by one
            prev->next = curr->next;                 // if find the destination then:
            curr = NULL;                             // romove the curr node and joint two nodes before and after curr
            break;                                   
        } else {
            prev = curr;                             // if not
            curr = curr->next;                       // update prev and curr
        }
    }
    g->noEdges--;
}
bool adjacent(Graph g, Vertex src, Vertex dest){
    assert(g!=NULL);                                 
    adjListNode* curr = g->List[src];                // recode the list[src] in curr
    while(curr!= NULL){                              // for every node in the list
        if (curr->w == dest) return true;            // if find the destination, return TURE
        else curr = curr->next;                      // if not, check the next node
    } 
    return false;                                    // if not found, return FALSE
}

int  numVerticies(Graph g){
    return g->noNodes;                               // return #nodes
}

/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
*
static void printnewList(adjListNode* newlist){
    while(newlist!=NULL){
        printf("VALUE: %d, weight %d\n",newlist->w, newlist->weight);
        newlist = newlist->next;
    }
}*/
AdjList outIncident(Graph g, Vertex v){
    if (g->List[v] == NULL) return NULL;
    /*adjListNode* curr = g->List[v];
    adjListNode* newlist = newNode(curr->w,curr->weight); 
    while(curr->next!= NULL){
        adjListNode* new = newNode(curr->next->w,curr->next->weight);
        new -> next = newlist;
        newlist = new;
        curr = curr->next;
    }
    printf("RETURNING NEWLIST FOR ITEM %d\n",v);
    printnewList(newlist);*/
    return g->List[v];            // list[v] is the list of adjacent vertices on outgoing edges from v
}
/*
 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/

AdjList inIncident(Graph g, Vertex v){
    adjListNode* newlist = newNode(-1, -1);      // create an adj list whick store nodes on incoming edges from v
    int i;
    for (i =0; i< g->noNodes; i++){          // for every adjacent list
        if (i == v) continue;
        adjListNode* curr = g->List[i];
        while(curr!= NULL){                      // if the curr node is not null
            if (curr->w == v){                   // check if it is incident with v
                addNode(newlist,i,curr->weight); // if true, store it in newlist
            }
            curr = curr-> next;                  // check the next node
        }
    }
    if (newlist->w == -1) return NULL;           // if newlist did not change, return NULL

    return newlist;                              // return newlist
}

void addNode (AdjList list, int i, int weight){
    if (list->w == -1){                          // if list is NULL
        list -> w = i;                           // update list
        list -> weight = weight;
        return;                                  // end fucntion
    } 
    adjListNode* new = newNode(i,weight);        // create a new node with i and weight
    adjListNode* next = list-> next;             
    new -> next = next;                          // add the node to the list
    list -> next = new;
}

void  showGraph(Graph g){
    assert(g!= NULL);                            // assert g is not NULL
    printf("#vertices=%d, #edges=%d\n\n",numVerticies(g),g->noEdges);
    int i;
    for(i =0; i<g->noNodes; i++){            // for every adjacency list
        adjListNode* curr = g->List[i];          
        printf("%d ----->", i);
        while (curr != NULL){
            printf("%d",curr->w);                // printf it's vertex and weight
            printf("(weight:%d)",curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}
void  freeGraph(Graph g){
    int i;
    for(i=0; i<g->noNodes;i++){              
        adjListNode* curr = g->List[i];          // free every node is the adjacency list
        while (curr!= NULL){
            adjListNode* prev = curr;
            curr = curr-> next;
            free(prev);                         
        }
    }
    free(g);                                    // then free the whole graphrep struct
}