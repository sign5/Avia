#include "graphutils.h"

void GraphUtils::DFSUtil(Graph &graph, int v, std::vector<bool> &visited, std::list<int> &steps){
    visited[v] = true;
    steps.push_back(v);
    for (int i = 0; i < graph.getNodeNum(); i++) {
        if (graph.hasThisArc(v, i) && !visited[i])
            DFSUtil(graph, i, visited, steps);
    }
}

bool GraphUtils::isConnectedFromUtoV(Graph graph, int u, int v) {
    if (!graph.hasThisNode(u) || !graph.hasThisNode(v)) return false;
    std::vector<bool> visited(graph.getNodeNum(), false);
    std::list<int> steps;
    DFSUtil(graph, u, visited, steps);
    if (!visited[v])
        return false;
    return true;
}

int minDistance(std::vector<int>& dist, std::vector<bool>& sptSet) {
    int min = INT_MAX, min_index;
    int n = dist.size();
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] < min)
            min = dist[v], min_index = v;
    return min_index;
}

std::list<int> GraphUtils::Dijkstra(Graph &graph, int start, int goal) {
    std::vector<int> dist(graph.getNodeNum(), INT_MAX);
    std::vector<bool> sptSet(graph.getNodeNum(), false);
    std::vector<int> parent(graph.getNodeNum(), -1);
    dist[start] = 0;
    for (int count = 0; count < graph.getNodeNum() - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < graph.getNodeNum(); v++) {
            if (!sptSet[v] && graph.hasThisArc(u, v) && dist[u] != INT_MAX && dist[u] + graph.getArcWeight(u, v) < dist[v]) {
                dist[v]	= dist[u] + graph.getArcWeight(u, v);
                parent[v] = u;
            }
        }
    }
    std::list<int> path;
    std::cout << "Дешёвейший путь из " << graph.getNodeName(start) << " в " << graph.getNodeName(goal) << ": ";
    if (dist[goal] == INT_MAX) {
        std::cout << " не найден\n";
        return path;
    }
    int curr = goal;
    while (curr != -1) {
        path.push_front(curr);
        curr = parent[curr];
    }
    for (auto itr = path.begin(); std::next(itr) != path.end(); itr++)
        std::cout << graph.getNodeName(*itr) << " -> ";
    std::cout << graph.getNodeName(goal) << "\nОбщая стоимость = " << dist[goal];
    return path;
}
