// Graph.c ... implementation of Graph ADT
// Written by Mingfang Jiao

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

// graph representation (adjacency List)
typedef struct GraphRep {
    adjListNode **edges; // List of weight
	int    nV;           // #vertices
	int    nE;           // #edges
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

AdjList newNode(Vertex dest, int weight){
    AdjList new = malloc(sizeof(adjListNode));
    new->w = dest;
    new->weight = weight;
    new->next = NULL;
    return new;
}

Graph newGraph(int noNodes){
    int v,w;
    assert(noNodes > 0);
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = noNodes;
	new->nE = 0;
	new->edges = calloc(nV,sizeof(adjListNode *));
	assert(new->edges != 0);
	return new;
}
	


void  insertEdge(Graph g, Vertex src, Vertex dest, int weight){
    assert(g != NULL);
    assert(validV(g,src));
    assert(validV(g,dest));
    int found = 0;
    AdjList curr = g->edges[src]; 
    while(curr->next != NULL){
        if(curr->w == dest){
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if(curr->w == dest){
        found = 1;
    }
    if(found == 0){
        AdjList insert = newNode(dest, weight); // insert edge to g->edges[src]
        curr->next = insert;
        insert = newNode(src, weight);          // insert edge to g->edges[dest]
        curr = g->edges[dest];
        g->edges[dest] = insert;
        insert->next = curr;
    }
    g->nE++;
}

void  removeEdge(Graph g, Vertex src, Vertex dest){
    assert(g != NULL);
    assert(validV(g,src));
    assert(validV(g,dest));    
    AdjList curr = g->edges[src];
    assert(curr != NULL);
    if(curr->w == dest){               // delete edge from g->edges[src];
        g->edges[src] = curr->next;
        free(curr);
    }else{
        AdjList befcurr = g->edges[src];  
        curr = befcurr->next;  
        while(curr != NULL){
            if(curr->w == dest){
                befcurr->next = curr->next;
                free(curr);
                break;
            }
            befcurr = befcurr->next;
            curr = curr->next;
        }
    }
    curr = g->edges[dest];
    assert(curr != NULL);
    if(curr->w == src){               // delete edge from g->edges[dest];
        g->edges[dest] = curr->next;
        free(curr);
    }else{
        AdjList befcurr = g->edges[dest];  
        curr = befcurr->next;  
        while(curr != NULL){
            if(curr->w == src){
                befcurr->next = curr->next;
                free(curr);
                break;
            }
            befcurr = befcurr->next;
            curr = curr->next;
        }
    }
    g->nE--;
}        
            
            



bool  adjacent(Graph g, Vertex src, Vertex dest){
    assert(g != NULL);
    assert(validV(g,src));
    assert(validV(g,dest));
    AdjList curr = g->edges[src];
    assert(curr != NULL);
    while(curr != NULL){
        if(curr->w == dest){
            return TRUE;
        }
        curr = curr->next;
    }
    return FALSE;
}

int  numVerticies(Graph g){
    return g->nV;
}


/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
**/
AdjList outIncident(Graph g, Vertex v){
    assert(v != NULL);
    assert(validV(g,v));
    AdjList outgoing = newNode(g->edges[v]->w,g->edges[v]->weight);
    AdjList outindex = outgoing;
    AdjList curr = g->edges[v]->next;
    while(curr != NULL){
        AdjList insert = newNode(curr->w,curr->weight);
        outindex->next = insert;
        curr = curr->next;
        outindex = outindex->next;
    }
    return outgoing;
}
/*

 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/
AdjList inIncident(Graph g, Vertex v){
    assert(v != NULL);
    assert(validV(g,v));
    AdjList incoming = newNode(-1,-1);
    AdjList index = incoming;
    int i = 0;
    while(i < g->nV){
        AdjList curr = g->edges[i];
        while(curr != NULL){
            if(curr->w == v){
                if(incoming->w == -1){
                    incoming = newNode(curr->w,curr->weight);
                    index = incoming;
                }else{
                    index->next = newNode(curr->w,curr->weight);
                    index = index->next;
                }
            }
            curr = curr->next;
        }
        i++;
    }
    return incoming;
}

void  showGraph(Graph g){
    assert(g != NULL);
    printf("#vertices = %d, #edges = %d\n",numVerticies(g),g->nE);
    for(int i =0; i < g->nV; i++){
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
    for(int i = 0; i < nV; i++){
        AdjList curr = g->adges[i];
        while(curr != NULL) {
            AdjList node = curr;
            curr = curr->next;
            free(node);
        }
    }
    free(g);
}
	
	
	
