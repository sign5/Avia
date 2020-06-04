#ifndef GRAPH_H
#define GRAPH_H

#include "flightdata.h"
#include "node.h"
#include <vector>
#include <limits.h>
#include <fstream>
#include <memory>
#include <exception/fileformatexception.h>

class Graph {
  private:
    std::vector<std::vector<Avia::FlightData *>> adj_mat;
    std::vector<Avia::Node> node_list;

  public:
    Graph();
    Graph(int node_num);
    Graph getTranpose();
    void init(int node_num);
    void printAdjMat() const;
    void clear();

    void readFromFile(std::string file) throw (FileFormatException);
    void writeToFile(std::string file);

    inline int getNodeNum() const { return this->node_list.size(); }
    int findNodeIdByName(std::string name) const;
    std::vector<std::vector<Avia::FlightData *>> getAdjMatrix() const { return this->adj_mat; }
    std::vector<Avia::Node> getNodeList() const { return this->node_list; }
    std::vector<std::pair<int, int>> getArcList() const;

    bool hasThisNode(int id) const { return id >= 0 && id < getNodeNum(); }
    bool hasThisNode(std::string name) const { return hasThisNode(findNodeIdByName(name)); }

    bool setArc(int u, int v, int w = 1);;
    bool setArc(int u, int v, Avia::FlightData *fd);
    bool setArc(std::string uname, std::string vname, Avia::FlightData *fd = NULL);
    bool setArc(int u, std::string vname, int w = 1);
    bool setArc(std::string uname, int v, int w = 1);
    bool removeArc(int u, int v);

    bool hasThisArc(int u, int v) const { return hasThisNode(u) && hasThisNode(v) && adj_mat[u][v] != NULL; }
    bool hasThisArc(std::string uname, std::string vname) const { return hasThisArc(findNodeIdByName(uname), findNodeIdByName(vname)); }
    int getArcWeight(int u, int v) const {
        if (u == v)
            return 0;
        if (hasThisArc(u, v))
            return this->adj_mat[u][v]->getPrice();
        else
            return NULL;
    }

    Avia::FlightData *getFlightData(int u, int v) const {
        if (u == v)
            return NULL;
        if (hasThisArc(u, v))
            return this->adj_mat[u][v];
        else
            return NULL;
    }

    void setArcWeight(int u, int v, float price);

    bool addNode(Avia::Node node);
    bool addNode(std::string nodename) { return addNode(Avia::Node(nodename));}
    bool removeNode(int id);
    bool removeNode(std::string nodename) { return removeNode(findNodeIdByName(nodename)); }
    bool isolateNode(int id);
    bool isolateNode(std::string nodename) { return isolateNode(findNodeIdByName(nodename)); }
    Avia::Node *getNodeByName(std::string name);
    Avia::Node *getNode(int id);
    std::string getNodeName(int id) const { return node_list[id].getName(); }
};
#endif
