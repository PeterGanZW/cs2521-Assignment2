// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "LanceWilliamsHAC.h"
#include "Dijkstra.h"
#define INFINITY 9999

typedef struct DendRep *DendrogramRep;
typedef struct Coords *Coordinates;

// struct that stores coordinates for the closest clusters
typedef struct Coords {
    int x, y;
} Coords;

typedef struct GraphRep {
    int nVert;
    AdjList *adjListArray;
} GraphRep;

// struct that holds all current dendrograms in an array
typedef struct DendRep {
    int size;
    Dendrogram *dendA;
} DendRep;

// initialise coord struct
Coordinates newCoordinates() {
    Coordinates coord;
    if ((coord = malloc(sizeof(Coords))) == NULL) {
        fprintf(stderr, "ERROR!\n");
        exit(1);
    }
    coord->x = coord->y = -1;
    return coord;
}

// initialise DendrogramRep struct
DendrogramRep newDendrogramRep(int nVert) {
    DendrogramRep dRep;
    if ((dRep = malloc(sizeof(DendRep))) == NULL) {
        fprintf(stderr, "ERROR!\n");
        exit(1);
    }
    dRep->dendA = malloc(sizeof(DNode)*nVert);
    dRep->size = nVert;
    return dRep;
}

// Creating a dendrogram, given a vertex and it's two children, if any
// left and right = NULL if there are no children
Dendrogram newDendrogram(int vertex, Dendrogram left, Dendrogram right) {
    Dendrogram d;
    if ((d = malloc(sizeof(DNode))) == NULL) {
        fprintf(stderr, "ERROR!\n");
        exit(1);
    }
    d->vertex = vertex;
    d->left = left;
    d->right = right;
    return d;
}

// initialse a new array to hold distances
float **initDistanceArray(int nVert) {
    assert(nVert > 0);
    float **dist;
    dist = malloc(nVert*sizeof(float *));
    assert(dist != 0);
    for (int i = 0; i < nVert; i++) {
        dist[i] = malloc(nVert*sizeof(float));
        assert(dist[i] != 0);
        for (int j = 0; j < nVert; j++) {
            dist[i][j] = 0;
        }
    }
    return dist;
}

// return edge we are looking for
AdjList findEdge(Graph g, Vertex src, Vertex dest) {
    AdjList tmp = g->adjListArray[src];
    while (tmp != NULL) {
        if (tmp->w == dest) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

// calculates initial distances between vertices and stores into 2D array
void initDistance(Graph g, float **dist, int src, int dest) {
    float weight1 = 0;
    float weight2 = 0;
    float wt;
    AdjList tmp;
    if ((tmp = findEdge(g, src, dest)) != NULL) {
        weight1 = tmp->weight;
    }
    if ((tmp = findEdge(g, dest, src)) != NULL) {
        weight2 = tmp->weight;
    }
    if ((weight1 == 0) && (weight2 == 0)) {
        dist[src][dest] = dist[dest][src] = INFINITY;
    } else {
        if (weight1 > weight2) {
            wt = weight1;
        } else {
            wt = weight2;
        }
        float distance = 1/wt;
        dist[src][dest] = dist[dest][src] = distance;
    }
}

// calculates the closest clusters from the distance array and returns coordinates to where it is in the array
Coordinates findClosestClusters(Coordinates coord, float **distanceArr, int size) {
    float smallest = INFINITY;
    int arr_size = size;
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            if ((i == j) || (distanceArr[i][j] == -1)) {
                continue;
            }
            if (distanceArr[i][j] < smallest) {
                smallest = distanceArr[i][j];
                coord->x = i;
                coord->y = j;
            }
        }
    }
    return coord;
}

// remove two clusters from the dRep array and merge them together
// then add that merged cluster to the index of the smallest of x and y
void removeClusters(int x, int y, DendrogramRep dRep) {
    int keep, remove;
    if (x < y) {
        keep = x;
        remove = y;
    } else {
        keep = y;
        remove = x;
    }
    
    Dendrogram new = newDendrogram(keep, dRep->dendA[keep], dRep->dendA[remove]);
    dRep->dendA[keep] = new;


    //Dendrogram removed = newDendrogram(-1, NULL, NULL);
    dRep->dendA[remove] = NULL;
}

// if clusters have been removed, change all values of the cluster with greatest index to -1
// makes sure that a cluster that has been removed isn't involed when calculating future closest distances
void restructureDistanceArr(float **distanceArr, int change, int size) {
    // for row
    for (int i = 0; i < size; i++) {
        /*if (i == change) {
            continue;
        }*/
        distanceArr[i][change] = -1;
    }

    // for column
    for (int i = 0; i < size; i++) {
        distanceArr[change][i] = -1;
    }
}

// calculates distances using single linkage method and updates the distance array
void singleLinkage(float **distanceArr, int x, int y, int size) {
    float smallest;
    // for rows
    for (int i = 0; i < size; i++) {
        float x_value = distanceArr[i][x];
        float y_value = distanceArr[i][y];
        if (x_value < y_value) {
            distanceArr[i][y] = x_value;
        } else {
            distanceArr[i][x] = y_value;
        }
    }

    // for columns
    for (int i = 0; i < size; i++) {
        float x_value = distanceArr[x][i];
        float y_value = distanceArr[y][i];
        if (distanceArr[x][i] < distanceArr[y][i]) {
            smallest = x_value;
            distanceArr[y][i] = distanceArr[x][i];
        } else {
            smallest = y_value;
            distanceArr[x][i] = smallest;
        }
    }
    int change;
    if (x < y) {
        change = y;
    } else {
        change = x;
    }
    restructureDistanceArr(distanceArr, change, size);
}

// calculates the distances using the complete linkage method and updates the distance array
void completeLinkage(float **distanceArr, int x, int y, int size) {
    float largest;
    // for rows
    for (int i = 0; i < size; i++) {
        float x_value = distanceArr[i][x];
        float y_value = distanceArr[i][y];
        if (x_value == INFINITY) {
            distanceArr[i][x] = distanceArr[i][y];
        } else if (y_value == INFINITY) {
            distanceArr[i][y] = distanceArr[i][x];
        } else if (x_value > y_value) {
            largest = x_value;
            distanceArr[i][y] = largest;
        } else {
            largest = y_value;
            distanceArr[i][x] = largest;
        }
    }

    // for columns
    for (int i = 0; i < size; i++) {
        float x_value = distanceArr[x][i];
        float y_value = distanceArr[y][i];
        if ((i == x) || (i == y)) {
            continue;
        } else if (x_value == INFINITY) {
            distanceArr[x][i] = distanceArr[y][i];
        } else if (y_value == INFINITY) {
            distanceArr[y][i] = distanceArr[x][i];
        } else if (x_value > y_value) {
            largest = x_value;
            distanceArr[y][i] = largest;
        } else {
            largest = y_value;
            distanceArr[x][i] = largest;
        }
    }
    int change;
    if (x < y) {
        change = y;
    } else {
        change = x;
    }
    restructureDistanceArr(distanceArr, change, size);
}

/*Calculate distances between each pair of vertices
    Create clusters for every vertex i, c[i]
    Let Dist(c[i], c[j]) represent the distance between cluster c[i] and c[j], initially it will represent the distance between i and j
    for k=1 to n-1:
        find two closest clusters, eg. c[i] and c[j]. If there are multiple alternatives, you can select any one of the pairs
        remove clusters c[i], c[j] from the collection and add a new cluster c[i+j] (with all vertices c[i] and c[j]) to the collection of clusters
        update dendrogram
        update distances, say Dist(c[i+j], c[k]), between the newly added cluster c[i+j] and the rest of the clusters c[k] into the collection using Lance-Williams formula
    end for
    return dendrogram
method = 1 represents "single linkage" and method = 2 represents "complete linkage" */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    // Calculate initial distances between each pair of vertices
    float **distanceArr = initDistanceArray(g->nVert);
    for (int i = 0; i < g->nVert; i++) {
        for (int j = 0; j < g->nVert; j++) {
            initDistance(g, distanceArr, i, j);
        }
    }

    // make a struct that will hold the dendrograms - initially, i = vertex
    DendrogramRep dRep = newDendrogramRep(g->nVert);
        for (int i = 0; i < g->nVert; i++) {
            Dendrogram d = newDendrogram(i, NULL, NULL);
            dRep->dendA[i] = d;
        }

    // Loop to find closest clusters and update distance array, using selected method
    for (int k = 1; k < g->nVert; k++) {
        Coordinates coord = newCoordinates();
        // find both clusters
        coord = findClosestClusters(coord, distanceArr, g->nVert);
        // if function doesn't find coordinates
        if ((coord->x == -1) && (coord->y == -1)) {
            exit(1);
        }
        // remove both clusters and merge them, then add it to the index of whichever was smaller
        removeClusters(coord->x, coord->y, dRep);
        // update distanceArr using Lance-Williams method
        if (method == 1) {
            singleLinkage(distanceArr, coord->x, coord->y, g->nVert);
        } else {
            completeLinkage(distanceArr, coord->x, coord->y, g->nVert);
        }
    }
    return dRep->dendA[0];
}

void freeDendrogram(Dendrogram d) {
    free(d);
}