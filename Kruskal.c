typedef Graph MSTree;
MSTree kruskalFindMST(Graph g)
{
    MSTree mst = newGraph();
    Edge eList[g->nV];
    edges(eList, g->nE, g);
    sortEdgeList(eList, g->nE);
    int i;
    Edge e;
    for(i = 0; mst->nE < g->nV-1; i++){
        e = eList[i];
        insertE(mst, e);
        if (hasCycle(mst)) removeE(mst, e);
    }
    return mst;
}

void shortestPath(Graph g, Vertex start, Vertex pred[], int dist[]){
    PQueue pq = newPQ(dist, nV(g));
    for (Vertex v = 0; v<nV(g); v++){
        pred[v] = -1; dist[v] = MAX_WT; 
        join(pq,v);
    }
    dist[start] = 0.0; reorder(pq, start);
    while(!empty(pq)){
        Vertex s = leave(pq);
        for(Vertex t = 0; t<nV(g); t++){
            int len = g->adj[s][t];
            if (len == NO_EDGE) continue;
            if (dist[s]+ len<dist[t]){
                pred[t] = s;
                dist[t] = dist[s] + len;
                reorder(pq, t);
            }
        }
    }
    
}