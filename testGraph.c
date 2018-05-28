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

  Graph g = newGraph(33);
  insertEdge(g,29,26,7);
  insertEdge(g,32,14,8);
  insertEdge(g,32,29,8);

  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
