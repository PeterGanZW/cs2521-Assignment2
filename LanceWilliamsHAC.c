// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include "LanceWilliamsHAC.h"
#include "Graph.c"
/*
typedef struct DNode *Dendrogram;
typedef struct DNode {
   int  vertex;
   Dendrogram left, right;
} DNode;
*/



/* 
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs) 
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods. 

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 * 
 */

/*
Step: Create an arra


*/

typedef struct Coordinates {
    int x;
    int y;
}Coordinates;

typedef Coordinates* Coord;


struct DentRep{
    int size;
    Dendrogram* dent;
};

typedef struct DentRep* DentRep;

Coord newCoord(int x, int y){
    Coord new = malloc(sizeof(Coordinates));
    new->x = x;
    new->y = y;
    return new;
}

DentRep newDentRep(int V){
    Dendrogram* dent = (Dendrogram*)malloc(V*sizeof(Dendrogram));
    int i;
    for(i=0; i<V;i++){
        dent[i] = (Dendrogram)malloc(sizeof(DNode));
        dent[i]->vertex = i;
        dent[i]->left = dent[i]->right = NULL;
    }
    DentRep rep = malloc(sizeof(struct DentRep));
    rep->size = V;
    rep-> dent = dent;
    return rep;
}

Coord static shortestDist(double** dist, int V){
    double shortest = DBL_MAX;
    int x = -1;
    int y = -1;
    int i;
    for(i = 0; i<V; i++){
        int j;
        for (j=0; j<i; j++){
            if (dist[i][j] == -1) continue;
            if (dist[i][j]<shortest){
                shortest = dist[i][j];
                x = i;
                y = j;
            }
        }
        for (j =i+1; j<V;j++){
            if (dist[i][j] == -1) continue;
            if (dist[i][j]<shortest){
                shortest = dist[i][j];
                x = i;
                y = j;
            }
        }
    }
    Coord new = newCoord(x, y);
    return new;
}

static void updateDent(Coord coord, Dendrogram* dent){
    //keep the smaller one of the x,y, and set the other one to NULL
    int x = coord->x;
    int y = coord->y;
    if (x<y){
        Dendrogram new = (Dendrogram)malloc(sizeof(DNode));
        new->vertex = x;
        new->left = dent[x];
        new->right = dent[y];
        dent[x] = new;
        dent[y] = NULL;
    } else {
        Dendrogram new = (Dendrogram)malloc(sizeof(DNode));
        new->vertex = y;
        new->left = dent[y];
        new->right = dent[x];
        dent[y] = new;
        dent[x] = NULL;
    }
}

static void Single(double** dist, Coord coord, int V){
    int x = coord->x;
    int y = coord->y;
    int i;
    for (i =0; i<V; i++){
        if (dist[x][i]>dist[y][i]){
            dist[x][i] = dist[y][i];
        } else {
            dist[y][i] = dist[x][i];
        }

        if (dist[i][x]>dist[i][y]){
            dist[i][x] = dist[i][y];
        } else {
            dist[i][y] = dist[i][x];
        }
    }
    if (x<y){
        for (i =0; i<V; i++){
            dist[y][i] = -1;
            dist[i][y] = -1;
        }
    } else {
        for (i =0; i<V; i++){
            dist[x][i] = -1;
            dist[i][x] = -1;
        }
    }
}

static void Complete(double** dist, Coord coord, int V){
    int x = coord->x;
    int y = coord->y;
    double inf = strtod("Inf", NULL);
    int i;
    for (i =0; i<V; i++){
        if (dist[x][i] == inf){
            dist[x][i] = dist[y][i];
        } else if (dist[y][i] == inf){
            dist[y][i] = inf;
        } else if (dist[x][i]>dist[y][i]){
            dist[y][i] = dist[x][i];
        } else {
            dist[x][i] = dist[y][i];
        }
        if (dist[i][x] == inf){
            dist[i][x] = dist[i][y];
        } else if (dist[i][y] == inf){
            dist[i][y] = inf;
        } else if (dist[i][x]>dist[i][y]){
            dist[i][y] = dist[i][x];
        } else {
            dist[i][x] = dist[i][y];
        }
    }
    if (x<y){
        for (i =0; i<V; i++){
            dist[y][i] = -1;
            dist[i][y] = -1;
        }
    } else {
        for (i =0; i<V; i++){
            dist[x][i] = -1;
            dist[i][x] = -1;
        }
    }
}



//return the max weight in double between two nodes from a graph, if the edge does not exist, return DBL_MAX
static double returnWeight(Graph g, int src, int dest){
    int value = 0;
    AdjList curr = outIncident(g, src);
    while (curr!=NULL){
        if (curr->w == dest){
            value = curr->weight;
        }
        curr = curr->next;
    }
    curr = outIncident(g, dest);
    while (curr!=NULL){
        if (curr->w == src && curr->weight > value){
            value = curr->weight;
        }
        curr = curr->next;
    }

    double returnValue = (double)value;
    return returnValue;
}

static double** calculateDistance(Graph g){
    int nV = g->noNodes;
    double** dist = (double**)malloc(nV*sizeof(double*));
    int i,j;
    for (i = 0; i<nV; i++)
        dist[i] = (double*) malloc(nV*sizeof(double));
    for (i=0; i<nV;i++){
        for (j=0; j<nV; j++){
            dist[i][j] = 1/returnWeight(g, i, j);
        }
    }
    return dist;
}


Dendrogram LanceWilliamsHAC(Graph g, int method){
    int V = numVerticies(g);
    DentRep dent = newDentRep(V);
    double** dist = calculateDistance(g);
    int i;
    for (i=0; i<V; i++){
        Coord c = shortestDist(dist,V);
        if (c->x == -1) break;
        updateDent(c, dent->dent);
        if (method == 0){
            Complete(dist,c,V);
        } else {
            Single(dist,c,V);
        }
    }
    return dent->dent[0];
}

void freeDendrogram(Dendrogram d){
    free(d);
}



