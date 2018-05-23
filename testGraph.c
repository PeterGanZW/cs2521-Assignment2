#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	// some very simple code to show you
	// how to use graph vis

  Graph g = newGraph(5);
  insertEdge(g,1,2,1);
  insertEdge(g,2,1,10);
  insertEdge(g,4,2,60);
  insertEdge(g,3,2,6);
  insertEdge(g,1,4,2);
  insertEdge(g,2,3,1);
  insertEdge(g,1,0,1);
  insertEdge(g,0,4,2);
  insertEdge(g,3,4,1);
  insertEdge(g,3,1,5);
  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
