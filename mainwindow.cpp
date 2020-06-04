#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view/graphgraphicsview.h"
#include "graphutils.h"
#include "inputdialog.h"
#include "flightdatainputdialog.h"
#include <QtGui>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include "qdebugstream.h"
#include <model/flightdata.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->statusBar->setStyleSheet("color: darkgrey");
    ui->console_text->setReadOnly(true);

    this->dataNeedSaving = false;
    this->setWindowTitle("Avia");
    QSignalMapper *m = new QSignalMapper(this);
    QShortcut *s1 = new QShortcut(QKeySequence("Alt+1"), this);
    QShortcut *s2 = new QShortcut(QKeySequence("Alt+2"), this);
    connect(s1, SIGNAL(activated()), m, SLOT(map()));
    connect(s2, SIGNAL(activated()), m, SLOT(map()));
    m->setMapping(s1, 0);
    m->setMapping(s2, 1);
    connect(m, SIGNAL(mapped(int)), ui->tabWidget, SLOT(setCurrentIndex(int)));
    QFont btnFont; btnFont.setPixelSize(18);
    ui->createGraphButton->setFont(btnFont);
    ui->openGraphButton->setFont(btnFont);

    ui->propertiesTable->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    ui->propertiesTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->propertiesTable->verticalHeader()->setDefaultSectionSize(24);

    this->graph = new Graph();
    this->scene = new GraphGraphicsScene(graph);
    this->view = new GraphGraphicsView();
    this->matrix = new GraphMatrixTable(graph);

    connect(matrix, SIGNAL(graphChanged()), scene, SLOT(reloadData()));
    connect(scene, SIGNAL(graphChanged()), matrix, SLOT(reloadData()));
    connect(this, SIGNAL(graphChanged()), scene, SLOT(reloadData()));
    connect(this, SIGNAL(graphChanged()), matrix, SLOT(reloadData()));
    connect(this, SIGNAL(graphChanged()), view, SLOT(redraw()));
    connect(this, SIGNAL(graphChanged()), this, SLOT(onGraphChanged()));
    connect(matrix, SIGNAL(graphChanged()), this, SLOT(onGraphChanged()));
    connect(scene, SIGNAL(graphChanged()), this, SLOT(onGraphChanged()));

    connect(view, &GraphGraphicsView::addNewNode, this, [this](QPointF pos){
        showNewNodeDialog(pos);
    });
    connect(view, &GraphGraphicsView::removeNode, this, [this](int id) {
        if (this->graph->removeNode(id))
            emit graphChanged();
    });
    connect(view, &GraphGraphicsView::isolateNode, this, [this](int id) {
        if(this->graph->isolateNode(id))
            emit graphChanged();
    });
    connect(view, &GraphGraphicsView::removeArc, this, [this](int u, int v) {
        if (graph->removeArc(u, v))
            emit graphChanged();
    });
    connect(view, &GraphGraphicsView::setArc, this, [this](int u, int v) {
        bool ok{};
        QList<QString> list = FlightDataInputDialog::getStrings(this, "Добавление новой дуги", &ok);
        QRegExp re("\\d+");
        if (ok && !list.empty()) {
            if (list[0].trimmed().isNull() || list[1].trimmed().isNull())
                return;
            int fromId = graph->findNodeIdByName(list[0].toStdString());
            int toId = graph->findNodeIdByName(list[1].toStdString());
            if (fromId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[0] + tr(" не существует"));
                return;
            }
            if (toId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[1] + tr(" не существует"));
                return;
            }
            if (!re.exactMatch(list[2])) {
                QMessageBox::critical(this, "Ошибка", tr("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной"));
                return;
            }

            int price = list[2].toInt();
            QDateTime departureDatetime = QDateTime::fromString(list[3],"dd.MM.yyyy hh:mm");
            QDateTime arrivalDatetime = QDateTime::fromString(list[4],"dd.MM.yyyy hh:mm");

            Avia::FlightData *fd = new Avia::FlightData(price, departureDatetime, arrivalDatetime);
            bool succeeded = graph->setArc(fromId, toId, fd);
            if (succeeded)
                emit graphChanged();
            else
                QMessageBox::critical(this, "Ошибка", "Ошибка при установке дуги");
        }
    });

    connect(view, &GraphGraphicsView::setArcFrom, this, [this](int u, int v) {
        bool ok{};
        QStringList prevValues = QStringList();
        prevValues << QString::fromStdString(graph->getNode(u)->getName());
        prevValues << QString::fromStdString(graph->getNode(v)->getName());
        prevValues << "";
        prevValues << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm");
        prevValues << QDateTime::currentDateTime().addSecs(60 * 60 * 6).toString("dd.MM.yyyy hh:mm");

        QList<QString> list = FlightDataInputDialog::getStrings(this, prevValues, "Добавление новой дуги", &ok);
        QRegExp re("\\d+");
        if (ok && !list.empty()) {
            if (list[0].trimmed().isNull() || list[1].trimmed().isNull())
                return;
            int fromId = graph->findNodeIdByName(list[0].toStdString());
            int toId = graph->findNodeIdByName(list[1].toStdString());
            if (fromId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[0] + tr(" не существует"));
                return;
            }
            if (toId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[1] + tr(" не существует"));
                return;
            }
            if (!re.exactMatch(list[2])) {
                QMessageBox::critical(this, "Ошибка", tr("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной"));
                return;
            }

            int price = list[2].toInt();
            QDateTime departureDatetime = QDateTime::fromString(list[3],"dd.MM.yyyy hh:mm");
            QDateTime arrivalDatetime = QDateTime::fromString(list[4],"dd.MM.yyyy hh:mm");

            Avia::FlightData *fd = new Avia::FlightData(price, departureDatetime, arrivalDatetime);
            bool succeeded = graph->setArc(fromId, toId, fd);
            if (succeeded)
                emit graphChanged();
            else
                QMessageBox::critical(this, "Ошибка", "Ошибка при установке дуги");
        }
    });

    connect(view, &GraphGraphicsView::editArc, this, [this](int u, int v) {
        bool ok{};
        QStringList prevValues = QStringList();
        prevValues << QString::fromStdString(graph->getNode(u)->getName());
        prevValues << QString::fromStdString(graph->getNode(v)->getName());
        Avia::FlightData* fd = this->graph->getFlightData(u, v);
        prevValues << QString::number(fd->getPrice());
        prevValues << fd->getDepartureDatetime().toString("dd.MM.yyyy hh:mm");
        prevValues << fd->getArrivalDatetime().toString("dd.MM.yyyy hh:mm");

        QList<QString> list = FlightDataInputDialog::getStrings(this, prevValues, "Изменение дуги", &ok);
        QRegExp re("\\d+");
        if (ok && !list.empty()) {
            if (list[0].trimmed().isNull() || list[1].trimmed().isNull())
                return;
            int fromId = graph->findNodeIdByName(list[0].toStdString());
            int toId = graph->findNodeIdByName(list[1].toStdString());
            if (fromId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[0] + tr(" не существует"));
                return;
            }
            if (toId == -1) {
                QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[1] + tr(" не существует"));
                return;
            }
            if (!re.exactMatch(list[2])) {
                QMessageBox::critical(this, "Ошибка", tr("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной"));
                return;
            }

            int price = list[2].toInt();
            QDateTime departureDatetime = QDateTime::fromString(list[3],"dd.MM.yyyy hh:mm");
            QDateTime arrivalDatetime = QDateTime::fromString(list[4],"dd.MM.yyyy hh:mm");

            Avia::FlightData *fd = new Avia::FlightData(price, departureDatetime, arrivalDatetime);
            bool succeeded = graph->setArc(fromId, toId, fd);
            if (succeeded)
                emit graphChanged();
            else
                QMessageBox::critical(this, "Ошибка", "Ошибка при установке дуги");
        }
    });

    connect(view, &GraphGraphicsView::startAlgorithm, this, [this](QString algo, int id) {
        GraphUtils graph_utils;
        QDebugStream qout(std::cout, ui->console_text);
        if (algo == "Find path") {
            bool ok;
            QString goal = QInputDialog::getText(this, "Find shortest path", "To node: ",QLineEdit::Normal, QString(), &ok);
            if (ok) {
                if (goal.isNull())
                    return;
                int toId = this->graph->findNodeIdByName(goal.toStdString());
                if (!this->graph->hasThisNode(toId)) {
                    QMessageBox::critical(this, "Ошибка", tr(":waNo node named ") + goal);
                    return;
                }
                this->ui->console_text->clear();
                qDebug() << graph_utils.isConnectedFromUtoV(*graph, id, toId);
                std::list<int> res = graph_utils.Dijkstra(*(this->graph), id, toId);
                emit startDemoAlgorithm(res, GraphDemoFlag::ArcAndNode);
            }
        }
    });
    connect(view, &GraphGraphicsView::editNode, this, [this](int id) {
        bool ok;
        QRegExp re("[a-zA-Z0-9-]{1,100}");
        QString newNodeName = QInputDialog::getText(this, "Add new node", "Name: ", QLineEdit::Normal, QString(), &ok);
        if (ok) {
            if (!re.exactMatch(newNodeName)) {
                QMessageBox::critical(this, "Ошибка", tr("Node's name contains only alphabetical or numeric characters\n")
                                      + tr("Length of the name mustn't be greater than 3 or smaller than 1"));
                return;
            }
            if (this->graph->hasThisNode(newNodeName.toStdString()))
                QMessageBox::critical(this, "Ошибка", "This name has been used by another node");
            else {
                this->graph->getNode(id)->setName(newNodeName.toStdString());
                emit graphChanged();
            }
        }
    });
    connect(view, &GraphGraphicsView::unSelect, this, [this]() {
        QAbstractItemModel* const mdl = this->ui->propertiesTable->model();
        mdl->removeRows(0,mdl->rowCount());
        mdl->removeColumns(0,mdl->columnCount());
    });
    connect(view, &GraphGraphicsView::selectedNode, this, [this](int id) {
        QAbstractItemModel* const mdl = this->ui->propertiesTable->model();
        mdl->removeRows(0,mdl->rowCount());
        mdl->removeColumns(0,mdl->columnCount());
        QStringList tableHeader;
        tableHeader << tr("ID") << tr("Название");
        this->ui->propertiesTable->setRowCount(2);
        this->ui->propertiesTable->setColumnCount(1);
        this->ui->propertiesTable->setVerticalHeaderLabels(tableHeader);

        this->ui->propertiesTable->setItem(0, 0, new QTableWidgetItem());
        this->ui->propertiesTable->item(0, 0)->setText(QString::number(id));
        this->ui->propertiesTable->item(0,0)->setFlags(Qt::ItemIsEnabled);

        this->ui->propertiesTable->setItem(1, 0, new QTableWidgetItem());
        this->ui->propertiesTable->item(1, 0)->setText(QString::fromStdString(this->graph->getNodeName(id)));
        this->ui->propertiesTable->item(1,0)->setFlags(Qt::ItemIsEnabled);
    });

    connect(matrix, &GraphMatrixTable::selectedArc, this, [this](int u, int v) {
        QAbstractItemModel* const mdl = this->ui->propertiesTable->model();
        mdl->removeRows(0,mdl->rowCount());
        mdl->removeColumns(0,mdl->columnCount());
        QStringList tableHeader;
        tableHeader << tr("Из") << tr("В") << tr("Стоимость") << tr("Дата отлёта") << tr("Дата прилёта");

        if (this->graph->getFlightData(u, v) != NULL) {
            this->ui->propertiesTable->setRowCount(5);
            this->ui->propertiesTable->setColumnCount(1);
            this->ui->propertiesTable->setColumnWidth(0, 200);
            this->ui->propertiesTable->setVerticalHeaderLabels(tableHeader);

            this->ui->propertiesTable->setItem(0, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(0, 0)->setText(QString::fromStdString(this->graph->getNodeName(u)));
            this->ui->propertiesTable->item(0,0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(1, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(1, 0)->setText(QString::fromStdString(this->graph->getNodeName(v)));
            this->ui->propertiesTable->item(1, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(2, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(2, 0)->setText((this->graph->getArcWeight(u, v) != INT_MAX) ? QString::number(this->graph->getArcWeight(u, v)) : "inf");
            this->ui->propertiesTable->item(2, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(3, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(3, 0)->setText(this->graph->getFlightData(u, v)->getDepartureDatetime().toString("dd.MM.yyyy hh:mm"));
            this->ui->propertiesTable->item(3, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(4, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(4, 0)->setText(this->graph->getFlightData(u, v)->getArrivalDatetime().toString("dd.MM.yyyy hh:mm"));
            this->ui->propertiesTable->item(4, 0)->setFlags(Qt::ItemIsEnabled);
        }
    });

    connect(view, &GraphGraphicsView::selectedArc, this, [this](int u, int v) {
        QAbstractItemModel* const mdl = this->ui->propertiesTable->model();
        mdl->removeRows(0,mdl->rowCount());
        mdl->removeColumns(0,mdl->columnCount());
        QStringList tableHeader;
        tableHeader << tr("Из") << tr("В") << tr("Стоимость") << tr("Дата отлёта") << tr("Дата прилёта");

        this->ui->propertiesTable->setRowCount(5);
        this->ui->propertiesTable->setColumnCount(1);
        this->ui->propertiesTable->setColumnWidth(0, 200);
        this->ui->propertiesTable->setVerticalHeaderLabels(tableHeader);

        if(this->graph->getFlightData(u, v) != NULL) {
            this->ui->propertiesTable->setItem(0, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(0, 0)->setText(QString::fromStdString(this->graph->getNodeName(u)));
            this->ui->propertiesTable->item(0,0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(1, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(1, 0)->setText(QString::fromStdString(this->graph->getNodeName(v)));
            this->ui->propertiesTable->item(1, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(2, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(2, 0)->setText((this->graph->getArcWeight(u, v) != INT_MAX) ? QString::number(this->graph->getArcWeight(u, v)) : "inf");
            this->ui->propertiesTable->item(2, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(3, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(3, 0)->setText(this->graph->getFlightData(u, v)->getDepartureDatetime().toString("dd.MM.yyyy hh:mm"));
            this->ui->propertiesTable->item(3, 0)->setFlags(Qt::ItemIsEnabled);

            this->ui->propertiesTable->setItem(4, 0, new QTableWidgetItem());
            this->ui->propertiesTable->item(4, 0)->setText(this->graph->getFlightData(u, v)->getArrivalDatetime().toString("dd.MM.yyyy hh:mm"));
            this->ui->propertiesTable->item(4, 0)->setFlags(Qt::ItemIsEnabled);
        }
    });

    connect(this, SIGNAL(startDemoAlgorithm(std::list<std::list<int> >,GraphDemoFlag)), scene, SLOT(demoAlgorithm(std::list<std::list<int> >,GraphDemoFlag)));
    connect(this, SIGNAL(startDemoAlgorithm(std::list<int>,GraphDemoFlag)), scene, SLOT(demoAlgorithm(std::list<int>,GraphDemoFlag)));
    connect(this, SIGNAL(startDemoAlgorithm(std::list<std::pair<int,int> >,GraphDemoFlag)), scene, SLOT(demoAlgorithm(std::list<std::pair<int,int> >,GraphDemoFlag)));

    ui->table_layout->addWidget(matrix, 1, Qt::AlignTop);
    view->setScene(scene);
    ui->draw_layout->addWidget(view);
    view->show();
    setWorkspaceEnabled(false);
}

void MainWindow::initWorkspace(QString filename, bool newfile) {
    try {
        if (!newfile) {
            graph->readFromFile(filename.toStdString());
            this->dataNeedSaving = false;
        }
        else {
            this->dataNeedSaving = true;
            bool okpressed = false;
            int n = QInputDialog::getInt(this, "Initialize graph with nodes", "Maximum 26 nodes that can be automatically generated", 0, 0, 26, 1, &okpressed);
            if (!okpressed)
                return;
            graph->init(n);
        }
        emit graphChanged();
    }
    catch(FileFormatException e) {
        QMessageBox::critical(this, "Ошибка", "Ошибка содержимого файла " + e.getFileName() + "\n" + e.getFuncName(), QMessageBox::Cancel);
    }
    catch(...) {
        setWorkspaceEnabled(false);
        QMessageBox::critical(this, "Ошибка", "Непредвиденная ошибка при чтении файла", QMessageBox::Cancel);
        if (workingFileName != "") setWorkspaceEnabled(true);
        return;
    }
    this->workingFileName = filename;
    int index = filename.toStdString().find_last_of("/\\");
    std::string input_trace_filename = filename.toStdString().substr(index+1);
    setWindowTitle(QString::fromStdString(input_trace_filename) + " - Avia");
    setWorkspaceEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graph;
    delete scene;
    delete view;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (dataNeedSaving) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Сохранить граф?",
                              "Изменения будут потеряны, если вы не сохраните их",
                              QMessageBox::No|QMessageBox::Yes|QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
            graph->writeToFile(workingFileName.toStdString());
        else if (reply == QMessageBox::Cancel)
            event->ignore();
    }
}

QString MainWindow::showOpenFileDialog() {
    return QFileDialog::getOpenFileName(this, tr("Открыть граф"), QDir::currentPath(), tr("Graph files (*.gph)"), 0, QFileDialog::DontUseNativeDialog);
}

QString MainWindow::showSaveFileDialog() {
    QString newfilename;
    for (int i = 1; true; i++) {
        std::ifstream is(QDir::currentPath().toStdString() + "/graph" + std::to_string(i) + ".gph");
        if (!is.good()) {
            newfilename = QString::fromStdString(QDir::currentPath().toStdString() + "/graph" + std::to_string(i) + ".gph");
            break;
        }
    }
    return QFileDialog::getSaveFileName(this, tr("Новый граф"), newfilename, tr("Graph files (*.gph)"), 0, QFileDialog::DontUseNativeDialog);
}

void MainWindow::showNewNodeDialog(QPointF pos) {
    bool ok;
    QRegExp re("[a-zA-Zа-яА-Я0-9-]{1,100}");
    QString newNodeName = QInputDialog::getText(this, "Добавление новой точки", "Имя: ", QLineEdit::Normal, QString(), &ok);
    if (ok) {
        if (!re.exactMatch(newNodeName)) {
            QMessageBox::critical(this, "Ошибка", tr("Имя точки должно соответствовать следующим требованиям:\n")
                                  + tr("допустимы только кириллические, латинские символы и дефис\n")
                                  + tr("длина имени от 1 до 100 символов"));
            return;
        }
        Avia::Node newNode(newNodeName.toStdString());
        newNode.setEuclidePos(pos);
        bool succeeded = graph->addNode(newNode);
        if (!succeeded)
            QMessageBox::critical(this, "Ошибка", "Данное имя уже используется");
        else
            emit graphChanged();
    }
}

void MainWindow::setWorkspaceEnabled(bool ready) {
    if (ready) ui->entry_widget->setVisible(false);
    ui->working_widget->setVisible(ready);
    ui->menuGraph->setEnabled(ready);
//    ui->menuAlgorithms->setEnabled(ready);
    foreach (QAction *action, ui->menuFile->actions())
        if (!action->menu() && !action->isSeparator() && action->text().contains("Save"))
            action->setEnabled(ready);
    if (ready)
       view->scale(1, 1);
}

void MainWindow::onGraphChanged() {
    this->dataNeedSaving = true;
    ui->statusBar->clearMessage();
    ui->console_text->clear();
}

void MainWindow::on_createGraphButton_clicked() {
    QString filename = showSaveFileDialog();
    if (!filename.isNull())
        initWorkspace(filename, true);
}

void MainWindow::on_openGraphButton_clicked()
{
   QString filename = showOpenFileDialog();
   if (!filename.isNull())
       initWorkspace(filename);
}

void MainWindow::on_actionSave_triggered() {
    if (dataNeedSaving) {
        this->dataNeedSaving = false;
        graph->writeToFile(workingFileName.toStdString());
        ui->statusBar->showMessage("Сохранено");
        QTimer::singleShot(2000, this, [this]() {
            this->ui->statusBar->clearMessage();
        });
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = showSaveFileDialog();
    if (!filename.isNull())
        graph->writeToFile(filename.toStdString());
}

void MainWindow::on_actionNew_Graph_triggered()
{
    QString filename = showSaveFileDialog();
    if (!filename.isNull())
        initWorkspace(filename, true);
}

void MainWindow::on_actionOpen_Graph_triggered()
{
    QString filename = showOpenFileDialog();
    if (!filename.isNull() && filename != workingFileName)
        initWorkspace(filename);
}

void MainWindow::on_actionCredits_triggered() {
    QMessageBox::about(this, "Об авторах программы", "Авторы:\nАлександр Бычков (@sign5),\nЕвгений Лукин (@NamelessGod),\nМнацакан Зурнаджян (@sphinx04)");
}

void MainWindow::on_actionExit_triggered() {
    QApplication::exit(0);
}

void MainWindow::on_actionAddNode_triggered() {
    showNewNodeDialog();
}

void MainWindow::on_actionAddArc_triggered() {
    bool ok{};
    QList<QString> list = FlightDataInputDialog::getStrings(this, "Добавление новой дуги", &ok);
    QRegExp re("\\d+");
    if (ok && !list.empty()) {
        if (list[0].trimmed().isNull() || list[1].trimmed().isNull())
            return;
        int fromId = graph->findNodeIdByName(list[0].toStdString());
        int toId = graph->findNodeIdByName(list[1].toStdString());
        if (fromId == -1) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[0] + tr(" не существует"));
            return;
        }
        if (toId == -1) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[1] + tr(" не существует"));
            return;
        }
        if (!re.exactMatch(list[2])) {
            QMessageBox::critical(this, "Ошибка", tr("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной"));
            return;
        }

        int price = list[2].toInt();
        QDateTime departureDatetime = QDateTime::fromString(list[3],"dd.MM.yyyy hh:mm");
        QDateTime arrivalDatetime = QDateTime::fromString(list[4],"dd.MM.yyyy hh:mm");

        Avia::FlightData *fd = new Avia::FlightData(price, departureDatetime, arrivalDatetime);
        bool succeeded = graph->setArc(fromId, toId, fd);
        if (succeeded)
            emit graphChanged();
        else
            QMessageBox::critical(this, "Ошибка", "Ошибка при установке дуги");
    }
}

// 1234
void MainWindow::on_actionEditArc_triggered() {
    for (auto gi : this->scene->selectedItems()) {
        auto agi = dynamic_cast<ArcGraphicsItem*>(gi);
        if (agi) {
            int u = agi->startItem()->node()->getId();
            int v = agi->endItem()->node()->getId();
            bool ok{};
            QStringList prevValues = QStringList();
            prevValues << QString::fromStdString(graph->getNode(u)->getName());
            prevValues << QString::fromStdString(graph->getNode(v)->getName());
            Avia::FlightData* fd = this->graph->getFlightData(u, v);
            prevValues << QString::number(fd->getPrice());
            prevValues << fd->getDepartureDatetime().toString("dd.MM.yyyy hh:mm");
            prevValues << fd->getArrivalDatetime().toString("dd.MM.yyyy hh:mm");

            QList<QString> list = FlightDataInputDialog::getStrings(this, prevValues, "Изменение дуги", &ok);
            QRegExp re("\\d*");
            if (ok && !list.empty()) {
                if (list[0].trimmed().isNull() || list[1].trimmed().isNull())
                    return;
                int fromId = graph->findNodeIdByName(list[0].toStdString());
                int toId = graph->findNodeIdByName(list[1].toStdString());
                if (fromId == -1) {
                    QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[0] + tr(" не существует"));
                    return;
                }
                if (toId == -1) {
                    QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + list[1] + tr(" не существует"));
                    return;
                }
                if (!re.exactMatch(list[2])) {
                    QMessageBox::critical(this, "Ошибка", tr("Некорректное значение стоимости. Стоимость должна быть положительной и целочисленной"));
                    return;
                }

                int price = list[2].toInt();
                QDateTime departureDatetime = QDateTime::fromString(list[3],"dd.MM.yyyy hh:mm");
                QDateTime arrivalDatetime = QDateTime::fromString(list[4],"dd.MM.yyyy hh:mm");

                Avia::FlightData *fd = new Avia::FlightData(price, departureDatetime, arrivalDatetime);
                bool succeeded = graph->setArc(fromId, toId, fd);
                if (succeeded)
                    emit graphChanged();
                else
                    QMessageBox::critical(this, "Ошибка", "Ошибка при установке дуги");
            }
        }
    }

//    bool ok{};
//    QList<QString> labelText;
//    labelText.push_back("Из точки: ");
//    labelText.push_back("В точку: ");
//    labelText.push_back("Вес: ");
//    QList<QString> list = InputDialog::getStrings(this, "Edit arc", labelText, &ok);
//    QRegExp re("\\d*");
//    if (ok && !list.empty() && re.exactMatch(list[2])) {
//        if (graph->hasThisArc(list[0].toStdString(), list[1].toStdString())) {
//            Avia::FlightData *fd = new Avia::FlightData(list[2].toFloat(), QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(10 * 60 * 60));
//            bool succeeded = graph->setArc(list[0].toStdString(), list[1].toStdString(), fd);
//            if (succeeded) {
//                emit graphChanged();
//                return;
//            }
//        }
//        QMessageBox::critical(this, "Ошибка", "Ошибка при редактировании дуги");
//    }
}

void MainWindow::on_actionDelNode_triggered() {
    bool ok;
    QString toDelName = QInputDialog::getText(this, "Удаление точки", "Имя точки: ", QLineEdit::Normal, QString(), &ok);
    if (ok) {
        bool succeeded = graph->removeNode(toDelName.toStdString());
        if (!succeeded)
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + toDelName + tr(" не существует"));
        else
            emit graphChanged();
    }
}

void MainWindow::on_actionDelArc_triggered()
{
    bool ok{};
    QList<QString> labelText;
    labelText.push_back("Из точки: ");
    labelText.push_back("В точку: ");
    QList<QString> list = InputDialog::getStrings(this, "Удаление дуги", labelText, &ok);
    if (ok && !list.empty()) {
        bool succeeded = graph->setArc(list[0].toStdString(), list[1].toStdString());
        if (succeeded)
            emit graphChanged();
        else
            QMessageBox::critical(this, "Ошибка", "Указанная дуга не существует");
    }
}

void MainWindow::on_shortestPathBtn_clicked() {
    ui->console_text->clear();
    GraphUtils graph_utils;
    QDebugStream qout(std::cout, ui->console_text);
    bool ok{};
    QList<QString> labels; labels.append("Из точки: "); labels.append("В точку: ");
    QList<QString> reply = InputDialog::getStrings(this, "Найти наибыстрейший путь", labels, &ok);
    if (ok) {
        if (reply[0].trimmed().isNull() || reply[1].trimmed().isNull())
            return;
        int fromId = graph->findNodeIdByName(reply[0].toStdString());
        int toId = graph->findNodeIdByName(reply[1].toStdString());
        if (!graph->hasThisNode(fromId)) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + reply[0] + tr(" не существует"));
            return;
        }
        if (!graph->hasThisNode(toId)) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + reply[1] + tr(" не существует"));
            return;
        }
        std::list<int> res = graph_utils.Dijkstra(*graph, fromId, toId);
        emit startDemoAlgorithm(res, GraphDemoFlag::ArcAndNode);
    }
}

void MainWindow::on_cheapestPathBtn_clicked() {
    ui->console_text->clear();
    GraphUtils graph_utils;
    QDebugStream qout(std::cout, ui->console_text);
    bool ok{};
    QList<QString> labels; labels.append("Из точки: "); labels.append("В точку: ");
    QList<QString> reply = InputDialog::getStrings(this, "Найти дешёвейший маршрут", labels, &ok);
    if (ok) {
        if (reply[0].trimmed().isNull() || reply[1].trimmed().isNull())
            return;
        int fromId = graph->findNodeIdByName(reply[0].toStdString());
        int toId = graph->findNodeIdByName(reply[1].toStdString());
        if (!graph->hasThisNode(fromId)) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + reply[0] + tr(" не существует"));
            return;
        }
        if (!graph->hasThisNode(toId)) {
            QMessageBox::critical(this, "Ошибка", tr("Точки с именем ") + reply[1] + tr(" не существует"));
            return;
        }
        std::list<int> res = graph_utils.Dijkstra(*graph, fromId, toId);
        emit startDemoAlgorithm(res, GraphDemoFlag::ArcAndNode);
    }
}

//void MainWindow::on_actionFind_shortest_path_triggered() {
//    on_shortestPathBtn_clicked();
//}

void MainWindow::on_actionFind_cheapest_path_triggered() {
    on_cheapestPathBtn_clicked();
}
