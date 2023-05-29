#include "main_window.h"
#include "ui_main_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Graph Algorithms");


    dfs_widget = new DFSAlgoWidget();
    warshall_widget = new WarshallAlgoWidget();
    dijkstra_widget = new DijkstraAlgoWidget();
    ford_fulkerson_widget = new FordFulkersonAlgoWidget();

    ui->verticalLayout_12->addWidget(dfs_widget);
    ui->verticalLayout_2->addWidget(warshall_widget);
    ui->verticalLayout_3->addWidget(dijkstra_widget);
    ui->verticalLayout_4->addWidget(ford_fulkerson_widget);

}

MainWindow::~MainWindow()
{

    delete ui;
}

