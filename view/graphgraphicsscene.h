#ifndef GRAPHGRAPHICSSCENE_H
#define GRAPHGRAPHICSSCENE_H

#include "model/graph.h"
#include "view/nodegraphicsitem.h"
#include "view/arcgraphicsitem.h"
#include <QGraphicsScene>
#include <QtWidgets>

enum GraphDemoFlag { OnlyNode, OnlyArc, ArcAndNode, Component, Coloring };

class GraphGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphGraphicsScene();
    GraphGraphicsScene(Graph *graph);
    Graph* graph() const;
    void setGraph(Graph *graph);
    int getArcId(int u, int v);

    friend class GraphGraphicsView;

public slots:
    void reloadData();
    void demoAlgorithm(std::list<std::pair<int, int>> listOfPair, GraphDemoFlag flag);
    void demoAlgorithm(std::list<int> listOfNum, GraphDemoFlag flag);
    void demoAlgorithm(std::list<std::list<int>> listOfList, GraphDemoFlag flag);

signals:
    void graphChanged();
    void needRedraw();

private:
    Graph *myGraph;
    std::vector<NodeGraphicsItem*> nodeItems;
    std::vector<ArcGraphicsItem*> arcItems;
    std::unique_ptr<QTimer> unique_timer;

    std::list<int> listOfNum;
    std::list<std::list<int>> listOfList;
    std::list<std::pair<int, int>> listOfPair;
    void resetAfterDemoAlgo();
};

#endif // GRAPHGRAPHICSSCENE_H
