#include "graphmatrixtable.h"
#include <QMessageBox>
#include <QDebug>

void GraphMatrixTable::defaultSetting() {

    this->horizontalHeader()->setMinimumSectionSize(55);
    this->horizontalHeader()->setDefaultSectionSize(55);
    this->horizontalHeader()->setCascadingSectionResizes(false);
    this->verticalHeader()->setMinimumSectionSize(50);
    this->verticalHeader()->setDefaultSectionSize(50);
    this->verticalHeader()->setCascadingSectionResizes(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    this->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
}

void GraphMatrixTable::setGraph(Graph *graph)
{

    this->myGraph = graph;
    if (myGraph == NULL) return;
    reloadData();
}

Graph* GraphMatrixTable::graph() const {

    return this->myGraph;
}

void GraphMatrixTable::adjustCell(int row, int column) {
    bool invalid = false;

    QRegExp re("\\d*");
    QString data = this->item(row, column)->text();
    data = data.trimmed();
    if (data.isNull() || data == "")
        data = "inf";

    if (re.exactMatch(data)) {
        if (data.toLongLong() <= 0)
            invalid = true;
        else if (data.toLongLong() >= INT_MAX) {
            data = "inf";
        }
    }
    else if (data != "inf")
        invalid = true;

    if (invalid) {
        QMessageBox msgWarning;
        msgWarning.setWindowTitle("Ошибка");
        msgWarning.setText("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной.\n"
                           "Чтобы удалить рейс введите \"inf\" или число большее " + QString::number(INT_MAX));
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.exec();

//        int price = data.toInt();
//        Avia::FlightData *fd = new Avia::FlightData(price, QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(60 * 60 * 6));
//        myGraph->setArc(row, column, fd);

        this->item(row, column)->setText((myGraph->getFlightData(row, column) != NULL) ? QString::number(myGraph->getFlightData(row, column)->getPrice()) : "inf");
    } else {
        if (data == "inf") {
            myGraph->removeArc(row, column);
            this->item(row, column)->setText("inf");
            return;
        } else {
            int price = data.toInt();
            Avia::FlightData *fd = new Avia::FlightData(price, QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(60 * 60 * 6));
            myGraph->setArc(row, column, fd);
        }
        emit graphChanged();
        emit selectedArc(row, column);
    }
}

GraphMatrixTable::GraphMatrixTable(Graph *myGraph)
{
    defaultSetting();
    setGraph(myGraph);

    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(adjustCell(int, int)));
    connect(this, &QTableWidget::itemSelectionChanged, this, [this](){
        for (QTableWidgetItem *item : this->selectedItems())
            adjustCell(item->row(), item->column());
    });
    connect(this, &GraphMatrixTable::currentCellChanged, this, [this](int u, int v) {
        try {
            emit selectedArc(u, v);
        }catch(...){}
    });
}

void GraphMatrixTable::reloadData() {

    disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(adjustCell(int, int)));

    this->clear();
    this->setRowCount(myGraph->getNodeNum());
    this->setColumnCount(myGraph->getNodeNum());
    QStringList table_header;
    for (Avia::Node node: myGraph->getNodeList()) {
        table_header << QString::fromStdString(node.getName());
    }
    this->setHorizontalHeaderLabels(table_header);
    this->setVerticalHeaderLabels(table_header);

    std::vector<std::vector<Avia::FlightData *>> adj_mat = myGraph->getAdjMatrix();
    for (int i = 0; i < myGraph->getNodeNum(); i++) {
        for (int j = 0; j < myGraph->getNodeNum(); j++) {

            this->setItem(i, j, new QTableWidgetItem);
            if (adj_mat[i][j] != NULL) {

               this->item(i, j)->setText(QString::fromStdString(std::to_string(adj_mat[i][j]->getPrice())));
               if (i != j) this->item(i, j)->setToolTip("Weight of the arc from node " +
                                            QString::fromStdString(myGraph->getNode(i)->getName()) + " to node " +
                                            QString::fromStdString(myGraph->getNode(j)->getName()));
            }
            else {
               this->item(i, j)->setText("inf");
               this->item(i, j)->setToolTip("No arc from node " +
                                            QString::fromStdString(myGraph->getNode(i)->getName()) + " to node " +
                                            QString::fromStdString(myGraph->getNode(j)->getName()));
            }
            this->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
        this->item(i, i)->setFlags(Qt::ItemIsEditable);
    }
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(adjustCell(int, int)));
}
