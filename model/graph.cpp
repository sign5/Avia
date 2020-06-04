#include "graph.h"
#include <math.h>
#include <iomanip>
#include <QDebug>
#include <algorithm>
#include <QDateTime>
#include <QDateTimeEdit>
#include <qdebugstream.h>
#include <mainwindow.h>
#include "view/nodegraphicsitem.h"
#include <exception/fileformatexception.h>

Graph::Graph() {
}

Graph::Graph(int node_num) {
    init(node_num);
}

void Graph::clear() {
    this->node_list.clear();
    this->adj_mat.clear();
}

void Graph::readFromFile(std::string file) throw (FileFormatException) {
    clear();
    std::ifstream in(file);
    if (!in)
        throw FileFormatException(QString::fromStdString(file), QString("file not existed"));

    int n; in >> n;
    if (n <= 0)
        throw FileFormatException(QString::fromStdString(file), QString("n <= 0"));
    std::string price, w, name;

    for (int i = 0; i < n; i++) {
        if (in.eof())
            throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading node names"));
        in >> name, addNode(Avia::Node(name, i));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (in.eof())
                throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading price"));
            in >> price;
            if (in.eof())
                throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading departureDateTime"));
            in >> w;
            QDateTime departureDateTime = QDateTime::fromString(QString::fromStdString(w),"dd.MM.yyyy_hh:mm");
            if (!departureDateTime.isValid())
                departureDateTime = QDateTime::currentDateTime();
            qDebug() << QString("departureDateTime") << departureDateTime;
            if (in.eof())
                throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading arrivalDateTime"));
            in >> w;
            QDateTime arrivalDateTime = QDateTime::fromString(QString::fromStdString(w),"dd.MM.yyyy_hh:mm");
            qDebug() << QString("arrivalDateTime") << arrivalDateTime.isValid();
            if (price != "INF") {
                if (!arrivalDateTime.isValid()) {
                    arrivalDateTime = QDateTime::currentDateTime();
                    std::cout << "Ошибка в данных о рейсе из " << getNode(i)->getName() << " в " << getNode(j)->getName();
                }
                Avia::FlightData* fd = new Avia::FlightData(std::stof(price), departureDateTime, arrivalDateTime);
                setArc(i, j, fd);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (in.eof())
            throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading node x position"));
        qreal x; in >> x;
        if (in.eof())
            throw new FileFormatException(QString::fromStdString(file), QString("readFromFile :: reading node y position"));
        qreal y; in >> y;
        node_list[i].setEuclidePos(QPointF(x, y));
    }
    in.close();
}

void Graph::writeToFile(std::string file) {

    std::ofstream out(file);
    out << getNodeNum() << "\n";
    for (int i = 0; i < getNodeNum(); i++)
        out << node_list[i].getName() << "\n";

    int max_length = 0;
    for (int i = 0; i < getNodeNum(); i++) {
        for (int j = 0; j < getNodeNum(); j++) {
            if (adj_mat[i][j] != NULL)
                max_length = std::max(max_length, (int)std::to_string(adj_mat[i][j]->getPrice()).length());
//            else
//                max_length = std::max(max_length, 3);
        }
    }

    for (int i = 0; i < getNodeNum(); i++) {
        for (int j = 0; j < getNodeNum(); j++) {
            if (hasThisArc(i, j))
                out << std::left << std::setw(max_length) << adj_mat[i][j]->getPrice() << " ";
            else
                out << std::left << std::setw(max_length) << "INF" << " ";

            if (hasThisArc(i, j)) {
                out << std::left << std::setw(max_length) << adj_mat[i][j]->getDepartureDatetime().toString("dd.MM.yyyy_hh:mm").toStdString() << " ";
            out << std::left << std::setw(max_length) << adj_mat[i][j]->getArrivalDatetime().toString("dd.MM.yyyy_hh:mm").toStdString() << " ";
            } else {
                out << std::left << std::setw(max_length) << "________________" << " ";
                out << std::left << std::setw(max_length) << "________________" << " ";
            }

//            adj_mat[i][j]->getDepartureDatetime().toString("dd.MM.yyyy hh:mm");
//            adj_mat[i][j]->getArrivalDatetime().toString("dd.MM.yyyy hh:mm");
        }
        out << "\n";
    }
    for (int i = 0; i < getNodeNum(); i++)
        out << node_list[i].getEuclidePos().rx() << " " << node_list[i].getEuclidePos().ry() << "\n";
    out.close();
}

void Graph::init(int node_num) {
    if (node_num <= 0) return;
    if (node_num > 26) {
        std::cout << "Maximum number of automatically gererated nodes is 26\n";
        return;
    }
    this->clear();
    this->adj_mat = std::vector<std::vector<Avia::FlightData *>>(node_num, std::vector<Avia::FlightData *>(node_num, NULL));
    for (int i = 0; i < node_num; i++) {
        this->node_list.push_back(Avia::Node(std::string(1, 'a' + i), i));
        this->adj_mat[i][i] = 0;
        QPointF point((1 - sin((i * 6.28) / node_num)) * node_num*NodeGraphicsItem::radius/2.,
                      (1 - cos((i * 6.28) / node_num)) * node_num*NodeGraphicsItem::radius/2.);
        this->node_list[i].setEuclidePos(point);
    }
}

Graph Graph::getTranpose() {

    Graph graph(getNodeNum());
    for (int u = 0; u < getNodeNum(); u++)
        for (int v = 0; v < getNodeNum(); v++)
//            if (adj_mat[u][v] != INT_MAX)
//                graph.setArc(v, u, adj_mat[u][v]);
    return graph;
}
void Graph::printAdjMat() const {

    int max_length = 0;
    for (int i = 0; i < getNodeNum(); i++) {
        for (int j = 0; j < getNodeNum(); j++) {
//            if (adj_mat[i][j] != INT_MAX)
//                max_length = std::max(max_length, (int)std::to_string(adj_mat[i][j]).length());
//            else
                max_length = std::max(max_length, 3);
        }
    }
    for (int i = 0; i < getNodeNum(); i++)
        max_length = std::max(max_length, (int)node_list[i].getName().length());

    std::cout << std::left << std::setw(max_length) << " " << " ";
    for (int i = 0; i < getNodeNum(); i++)
        std::cout << std::left << std::setw(max_length) << node_list[i].getName() << " ";
    std::cout << "\n";

    for (int i = 0; i < getNodeNum(); i++) {
        std::cout << std::left << std::setw(max_length) << node_list[i].getName() << " ";
        for (int j = 0; j < getNodeNum(); j++) {
//            if (adj_mat[i][j] != INT_MAX)
//                std::cout << std::left << std::setw(max_length) << adj_mat[i][j] << " ";
//            else
//                std::cout << std::left << std::setw(max_length) << "INF" << " ";
        }
        std::cout << std::endl;
    }
}

int Graph::findNodeIdByName(std::string name) const {
    for (int i = 0; i < getNodeNum(); i++)
        if (node_list[i].getName() == name)
            return i;
    return -1;
}

bool Graph::setArc(int u, int v, Avia::FlightData * fd) {
    if (u == v) return true;
    if (hasThisArc(u, v)) {
        this->adj_mat[u][v] = fd;
        return true;
    }
    if (hasThisNode(u) && hasThisNode(v)) {
        if (fd == NULL) {
            removeArc(u, v);
            return true;
         }
        this->adj_mat[u][v] = fd;
        this->node_list[u].incNegativeDeg();
        this->node_list[v].incPositiveDeg();

        return true;
    }
    return false;
}

bool Graph::setArc(std::string uname, std::string vname, Avia::FlightData *fd) {
    return setArc(findNodeIdByName(uname), findNodeIdByName(vname), fd);
}

bool Graph::setArc(int u, std::string vname, int w) {
    return setArc(u, findNodeIdByName(vname), w);
}

bool Graph::setArc(std::string uname, int v, int w) {
    return setArc(findNodeIdByName(uname), v, w);
}

bool Graph::removeArc(int u, int v) {
    if (u == v)
        return true;

    if (hasThisNode(u) && hasThisNode(v) && hasThisArc(u, v)) {
        this->adj_mat[u][v] = NULL;
        this->node_list[u].decNegativeDeg();
        this->node_list[v].decPositiveDeg();
        return true;
    }
    return false;
}

void Graph::setArcWeight(int u, int v, float price) {
    if (hasThisArc(u, v))
        return this->adj_mat[u][v]->setPrice(price);
}

bool Graph::addNode(Avia::Node node) {
    if (hasThisNode(node.getName())) return false;

    node.setId(getNodeNum());
    this->node_list.push_back(node);
    std::vector<Avia::FlightData *> new_row(getNodeNum(), NULL);
    new_row[getNodeNum() - 1] = 0;
    adj_mat.push_back(new_row);
    for (int i = 0; i < getNodeNum(); i++)
        adj_mat[i].push_back(NULL);
    return true;
}

bool Graph::removeNode(int id) {
    for (int v = 0; v < getNodeNum(); v++) {
        removeArc(v, id);
        removeArc(id, v);
    }
    if (!hasThisNode(id)) return false;
    this->node_list.erase(this->node_list.begin() + id);
    this->adj_mat.erase(this->adj_mat.begin() + id);
    for (int i = 0; i < getNodeNum(); i++) {
        adj_mat[i].erase(adj_mat[i].begin() + id);
        node_list[i].setId(i);
    }
    return true;
}

bool Graph::isolateNode(int id) {
    if (!hasThisNode(id)) return false;
    for (int v = 0; v < getNodeNum(); v++) {
        removeArc(v, id);
        removeArc(id, v);
    }
    this->adj_mat[id] = std::vector<Avia::FlightData *>(getNodeNum(), NULL);
    for (int i = 0; i < getNodeNum(); i++)
        adj_mat[i][id] = NULL;
    this->adj_mat[id][id] = 0;
    return true;
}

Avia::Node *Graph::getNodeByName(std::string name) {
    return getNode(findNodeIdByName(name));
}

Avia::Node *Graph::getNode(int id) {
    if (!hasThisNode(id))
        return nullptr;
    return &node_list[id];
}

std::vector<std::pair<int, int>> Graph::getArcList() const {
    std::vector<std::pair<int, int>> res;
    for (int u = 0; u < getNodeNum(); u++)
        for (int v = 0; v < getNodeNum(); v++)
            if (hasThisArc(u, v))
                res.push_back(std::make_pair(u, v));
    return res;
}

bool Graph::setArc(int u, int v, int w) {
    Avia::FlightData *fd = new Avia::FlightData((float)w, QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(10 * 60 * 60));
    return setArc(u, v, fd);
}
