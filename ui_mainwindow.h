/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QDateTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Graph;
    QAction *actionOpen_Graph;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionCredits;
    QAction *actionExit;
    QAction *actionAddNode;
    QAction *actionAddArc;
    QAction *actionEditArc;
    QAction *actionDelNode;
    QAction *actionDelArc;
    QAction *actionFind_shortest_path;
    QAction *actionFind_cheapest_path;

    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *entry_widget;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_8;
    QPushButton *createGraphButton;
    QPushButton *openGraphButton;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *working_widget;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *main_layout;
    QTabWidget *tabWidget;
    QWidget *tab_drawing;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *draw_layout;
    QWidget *tab_table;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *table_layout;
    QFrame *line;
    QTextEdit *console_text;
    QWidget *utils;
    QVBoxLayout *verticalLayout;
    QFrame *line_2;
    QVBoxLayout *button_layout;
    QVBoxLayout *verticalLayout_7;
    QLabel *properties_label;
    QTableWidget *propertiesTable;
    QFrame *line_4;
    QLabel *algorithms_label;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuGraph;
    QMenu *menuAdd;
    QMenu *menuEdit;
    QMenu *menuDelete;
//    QMenu *menuAlgorithms;
    QStatusBar *statusBar;

    QPushButton *shortestPathBtn;
    QPushButton *cheapestPathBtn;

    QFormLayout *formLayout;
    QLabel *lblDeparture;
    QLabel *lblArrival;
    QDateTimeEdit *dateTimeEditDeparture;
    QDateTimeEdit *dateTimeEditArrival;

    QTextEdit *getConsole() {
        return this->console_text;
    }

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setMinimumSize(QSize(720, 540));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));

        actionNew_Graph = new QAction("&Новый граф", MainWindow);
        actionNew_Graph->setObjectName(QStringLiteral("actionNew_Graph"));
        actionOpen_Graph = new QAction("&Открыть граф", MainWindow);
        actionOpen_Graph->setObjectName(QStringLiteral("actionOpen_Graph"));
        actionSave = new QAction("&Сохранить", MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_As = new QAction("Сохранить &как", MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionCredits = new QAction("&Об авторах", MainWindow);
        actionCredits->setObjectName(QStringLiteral("actionCredits"));
        actionExit = new QAction("&Выйти", MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));

        actionAddNode = new QAction("&Узел", MainWindow);
        actionAddNode->setObjectName(QStringLiteral("actionAddNode"));
        actionAddArc = new QAction("&Рейс", MainWindow);
        actionAddArc->setObjectName(QStringLiteral("actionAddArc"));
        actionEditArc = new QAction("&Рейс", MainWindow);
        actionEditArc->setObjectName(QStringLiteral("actionEditArc"));
        actionDelNode = new QAction("&Узел", MainWindow);
        actionDelNode->setObjectName(QStringLiteral("actionDelNode"));
        actionDelArc = new QAction("&Рейс", MainWindow);
        actionDelArc->setObjectName(QStringLiteral("actionDelArc"));

//        actionFind_shortest_path = new QAction("Find shortest path", MainWindow);
//        actionFind_shortest_path->setObjectName(QStringLiteral("actionFind_shortest_path"));

        actionFind_cheapest_path = new QAction("Найти дешёвейший маршрут", MainWindow);
        actionFind_cheapest_path->setObjectName(QStringLiteral("actionFind_cheapest_path"));

        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        entry_widget = new QWidget(centralWidget);
        entry_widget->setObjectName(QStringLiteral("entry_widget"));
        horizontalLayout_12 = new QHBoxLayout(entry_widget);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout_12->addItem(horizontalSpacer);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_2);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_5);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_6);
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_8);

        createGraphButton = new QPushButton("Создать новый граф", entry_widget);
        createGraphButton->setObjectName(QStringLiteral("createGraphButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createGraphButton->sizePolicy().hasHeightForWidth());
        createGraphButton->setSizePolicy(sizePolicy);

        verticalLayout_9->addWidget(createGraphButton);

        openGraphButton = new QPushButton("Открыть существующий граф", entry_widget);
        openGraphButton->setObjectName(QStringLiteral("openGraphButton"));
        sizePolicy.setHeightForWidth(openGraphButton->sizePolicy().hasHeightForWidth());
        openGraphButton->setSizePolicy(sizePolicy);

        verticalLayout_9->addWidget(openGraphButton);
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_9);
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_7);
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_4);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout_9->addItem(verticalSpacer_3);
        horizontalLayout_12->addLayout(verticalLayout_9);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout_12->addItem(horizontalSpacer_2);

        horizontalLayout->addWidget(entry_widget);

        working_widget = new QWidget(centralWidget);
        working_widget->setObjectName(QStringLiteral("working_widget"));
        horizontalLayout_9 = new QHBoxLayout(working_widget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        main_layout = new QVBoxLayout();
        main_layout->setSpacing(6);
        main_layout->setObjectName(QStringLiteral("main_layout"));
        main_layout->setContentsMargins(6, -1, -1, -1);
        tabWidget = new QTabWidget(working_widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_drawing = new QWidget();
        tab_drawing->setObjectName(QStringLiteral("tab_drawing"));
        horizontalLayout_2 = new QHBoxLayout(tab_drawing);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        draw_layout = new QVBoxLayout();
        draw_layout->setSpacing(6);
        draw_layout->setObjectName(QStringLiteral("draw_layout"));

        horizontalLayout_2->addLayout(draw_layout);

        tabWidget->addTab(tab_drawing, QString());
        tab_table = new QWidget();
        tab_table->setObjectName(QStringLiteral("tab_table"));
        verticalLayout_3 = new QVBoxLayout(tab_table);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        table_layout = new QVBoxLayout();
        table_layout->setSpacing(0);
        table_layout->setObjectName(QStringLiteral("table_layout"));

        verticalLayout_3->addLayout(table_layout);

        tabWidget->addTab(tab_table, QString());

        main_layout->addWidget(tabWidget);

        line = new QFrame(working_widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        main_layout->addWidget(line);

        console_text = new QTextEdit(working_widget);
        console_text->setObjectName(QStringLiteral("console_text"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(console_text->sizePolicy().hasHeightForWidth());
        console_text->setSizePolicy(sizePolicy1);
        console_text->setMaximumSize(QSize(16777215, 130));

        QFont btnFont; btnFont.setPixelSize(20);
        console_text->setFont(btnFont);

        main_layout->addWidget(console_text);

        horizontalLayout_9->addLayout(main_layout);

        utils = new QWidget(working_widget);
        utils->setObjectName(QStringLiteral("utils"));
        utils->setMaximumSize(QSize(270, 16777215));
        verticalLayout = new QVBoxLayout(utils);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(utils);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        button_layout = new QVBoxLayout();
        button_layout->setSpacing(6);
        button_layout->setObjectName(QStringLiteral("button_layout"));

        algorithms_label = new QLabel("Поиск маршрута", utils);
        algorithms_label->setObjectName(QStringLiteral("algorithms_label"));
        button_layout->addWidget(algorithms_label);

        {
            // TODO shortestPath
//            shortestPathBtn = new QPushButton("Find shortest path", utils);
//            shortestPathBtn->setObjectName(QStringLiteral("shortestPathBtn"));
//            button_layout->addWidget(shortestPathBtn);

            cheapestPathBtn = new QPushButton("Найти дешёвейший маршрут", utils);
            cheapestPathBtn->setObjectName(QStringLiteral("cheapestPathBtn"));
            button_layout->addWidget(cheapestPathBtn);
        }

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, -1, 6);
        properties_label = new QLabel("Данные о маршрутах", utils);
        properties_label->setObjectName(QStringLiteral("properties_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(properties_label->sizePolicy().hasHeightForWidth());
        properties_label->setSizePolicy(sizePolicy2);

        verticalLayout_7->addWidget(properties_label);

        propertiesTable = new QTableWidget(utils);
        propertiesTable->setObjectName(QStringLiteral("propertiesTable"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(propertiesTable->sizePolicy().hasHeightForWidth());
        propertiesTable->setSizePolicy(sizePolicy3);
        propertiesTable->setMaximumSize(QSize(16777215, 16777215));
        propertiesTable->horizontalHeader()->setVisible(false);

        verticalLayout_7->addWidget(propertiesTable);
        button_layout->addLayout(verticalLayout_7);

        line_4 = new QFrame(utils);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        button_layout->addWidget(line_4);

//        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        button_layout->addItem(verticalSpacer_10);

//        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        button_layout->addItem(verticalSpacer);
        verticalLayout->addLayout(button_layout);
        horizontalLayout_9->addWidget(utils);
        horizontalLayout->addWidget(working_widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 22));
        menuFile = new QMenu("&Файл", menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuGraph = new QMenu("&Граф", menuBar);
        menuGraph->setObjectName(QStringLiteral("menuGraph"));
        menuAdd = new QMenu("&Добавить", menuGraph);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuEdit = new QMenu("&Редактировать", menuGraph);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuDelete = new QMenu("&Удалить", menuGraph);
        menuDelete->setObjectName(QStringLiteral("menuDelete"));

        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuGraph->menuAction());
        menuFile->addAction(actionNew_Graph);
        menuFile->addAction(actionOpen_Graph);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionCredits);
        menuFile->addAction(actionExit);
        menuGraph->addAction(menuAdd->menuAction());
        menuGraph->addAction(menuEdit->menuAction());
        menuGraph->addAction(menuDelete->menuAction());
        menuAdd->addAction(actionAddNode);
        menuAdd->addAction(actionAddArc);
        menuEdit->addAction(actionEditArc);
        menuDelete->addAction(actionDelNode);
        menuDelete->addAction(actionDelArc);
//        menuAlgorithms = new QMenu(menuBar);
//        menuAlgorithms->setObjectName(QStringLiteral("menuAlgorithms"));
//        menuBar->addAction(menuAlgorithms->menuAction());
//        menuAlgorithms->addAction(actionFind_shortest_path);
//        menuAlgorithms->addAction(actionFind_cheapest_path);
        tabWidget->setTabText(tabWidget->indexOf(tab_drawing), QApplication::translate("MainWindow", "Карта перелётов", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_table), QApplication::translate("MainWindow", "Данные о перелётах", Q_NULLPTR));

#ifndef QT_NO_SHORTCUT
        actionNew_Graph->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
        actionOpen_Graph->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Alt+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT

        retranslateUi(MainWindow);
        tabWidget->setCurrentIndex(0);
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow) {}
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
