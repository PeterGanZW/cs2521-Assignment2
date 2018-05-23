// Dijkstra ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>


int main(){
    // some very simple code to show you
    // how to use graph vis

  Graph g = newGraph(5);
  insertEdge(g,1,2,1);
  insertEdge(g,2,1,10);
  insertEdge(g,4,2,60);
  insertEdge(g,3,2,6);
  insertEdge(g,3,4,4);
  insertEdge(g,3,1,3);
  removeEdge(g,3,2);
  showGraph(g);

    // draws the graph
  graphVis(g, DEFAULT);
    return EXIT_SUCCESS;
}
