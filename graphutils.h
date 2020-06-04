#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include "model/graph.h"
#include <queue>
#include <stack>
#include <list>

class GraphUtils {

private:
    void DFSUtil(Graph &graph, int v, std::vector<bool> &visited, std::list<int> &steps);

public:
    std::list<int> Dijkstra(Graph &graph, int start, int goal);
    bool isConnectedFromUtoV(Graph graph, int u, int v);
};

#endif
