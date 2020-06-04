#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "model/graph.h"
#include "view/graphgraphicsscene.h"
#include "view/graphmatrixtable.h"
#include "view/graphgraphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onGraphChanged();

    void on_openGraphButton_clicked();
    void on_createGraphButton_clicked();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionNew_Graph_triggered();
    void on_actionOpen_Graph_triggered();
    void on_actionCredits_triggered();
    void on_actionExit_triggered();
    void on_actionAddNode_triggered();
    void on_actionAddArc_triggered();
    void on_actionEditArc_triggered();
    void on_actionDelNode_triggered();
    void on_actionDelArc_triggered();

    void on_shortestPathBtn_clicked();
    void on_cheapestPathBtn_clicked();

//    void on_actionFind_shortest_path_triggered();
    void on_actionFind_cheapest_path_triggered();

signals:
    void graphChanged();
    void startDemoAlgorithm(std::list<std::pair<int, int>> listOfPair, GraphDemoFlag flag);
    void startDemoAlgorithm(std::list<int> listOfNum, GraphDemoFlag flag);
    void startDemoAlgorithm(std::list<std::list<int>> listOfList, GraphDemoFlag flag);

protected:
    void closeEvent(QCloseEvent *event);

private:
    static MainWindow* instance;
    static bool inited;
    QString workingFileName;
    Ui::MainWindow *ui;
    GraphGraphicsScene *scene;
    GraphGraphicsView *view;
    GraphMatrixTable *matrix;
    Graph *graph;
    bool dataNeedSaving;

    void askToSave();
    QString showOpenFileDialog();
    QString showSaveFileDialog();
    void showNewNodeDialog(QPointF pos = QPointF(0, 0));
    void showNewArcDialog();
    void setWorkspaceEnabled(bool ready);
    void initWorkspace(QString filename, bool newfile = false);
};

#endif // MAINWINDOW_H
