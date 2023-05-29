#include "warshall_algo_widget.h"
#include "ui_warshall_algo_widget.h"

WarshallAlgoWidget::WarshallAlgoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarshallAlgoWidget)
{
    ui->setupUi(this);

    size_list << "2x2" << "3x3" << "4x4" << "5x5" << "6x6" << "7x7" << "8x8" << "9x9" << "10x10";

    status_bar = new QStatusBar();
    ui->verticalLayout_20->insertWidget(0, status_bar);

    ui->cb_size_selection->addItems(size_list);

    major_matrix_table = new QTableWidget();

    ui->pb_launch->setDisabled(true);

    connect(ui->pb_apply, &QPushButton::clicked, this, &WarshallAlgoWidget::onPbApply);
    connect(ui->pb_launch, &QPushButton::clicked, this, &WarshallAlgoWidget::onPbLaunch);
}

WarshallAlgoWidget::~WarshallAlgoWidget()
{
    delete ui;
}

void WarshallAlgoWidget::onPbApply() {
     qDebug() << "До" << ui->verticalLayout_22->count();

     QList<QWidget *> widgets_left = ui->scrollAreaWidgetContents_2->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

     qDebug() << widgets_left;

     foreach(QWidget * child, widgets_left){
         qDebug() << "Удаление матрицы смежности";
        child->deleteLater();
     }

     QList<QWidget *> widgets_right = ui->scrollAreaWidgetContents->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

     qDebug() << widgets_right;

     foreach(QWidget * child, widgets_right){
         qDebug() << "Удаление результата";
        child->deleteLater();
     }


    qDebug() << "После" << ui->verticalLayout_22->count();
    int size = ui->cb_size_selection->currentIndex() + 2;

    adjacency_matrix_table = new QTableWidget();

    adjacency_matrix_table->setColumnCount(size);
    adjacency_matrix_table->setRowCount(size);

    major_matrix_table->setColumnCount(size);
    major_matrix_table->setRowCount(size);



    for (uint i = 0; i < (uint)adjacency_matrix_table->columnCount(); i++) {
        adjacency_matrix_table->setColumnWidth(i, 50);
    }
    for (uint i = 0; i < (uint)adjacency_matrix_table->rowCount(); i++) {
        adjacency_matrix_table->setRowHeight(i, 50);
    }

    ui->verticalLayout_22->addWidget(adjacency_matrix_table);

    ui->pb_launch->setDisabled(false);


}

void WarshallAlgoWidget::onPbLaunch()
{
    checkFillArray();

    warshallAlgo();

    qDebug() << "Что-то типа решения" << major_arr;

    ui->verticalLayout_6->addWidget(major_matrix_table);


}

void WarshallAlgoWidget::checkFillArray() {

        if (ui->verticalLayout_22->itemAt(0) == 0) {
            status_bar->showMessage("Нет матрицы связности");
        } else {
            qDebug() << "Матрица есть";
        }

        uint vertex_count = adjacency_matrix_table->rowCount();



        major_arr.resize(vertex_count);
        for (uint i = 0; i < vertex_count; i++) {
            major_arr[i].resize(vertex_count);
        }

        minor_arr.resize(vertex_count);
        for (uint i = 0; i < vertex_count; i++) {
            minor_arr[i].resize(vertex_count);
        }



    for (uint i = 0; i < vertex_count; i++) {
        for (uint j = 0; j < vertex_count; j++) {

            major_arr[i][j] = adjacency_matrix_table->item(i, j)->text().toInt();
        }
    }

    for (uint i = 0; i < vertex_count; i++) {
        for (uint j = 0; j < vertex_count; j++) {

           qDebug() << major_arr[i][j];
        }
    }
    qDebug() << major_arr;
}

void WarshallAlgoWidget::warshallAlgo() {

    int matrix_size = adjacency_matrix_table->rowCount();



    for (int j = 0; j < matrix_size; j++){
        minor_arr = major_arr;
        for (int i = 0; i < matrix_size; i++) {
            if (major_arr[i][j] == 0) {
                for (int x = 0; x < matrix_size; x++) {
                    minor_arr[i][x] = major_arr[i][x];
                }
            } else {
                for (int x = 0; x < matrix_size; x++) {
                    minor_arr[i][x] = minor_arr[i][x] || major_arr[j][x];
                }
            }
            qDebug() << "Minor matrix: " <<j << " " << minor_arr << "\n";
        }

        major_arr = minor_arr;
        setResultMatrixTable();

    }

}

void WarshallAlgoWidget::setResultMatrixTable() {

    int size = major_matrix_table->rowCount();

    for (uint i = 0; i < (uint)size; i++) {
        major_matrix_table->setColumnWidth(i, 50);
    }
    for (uint i = 0; i < (uint)size; i++) {
        major_matrix_table->setRowHeight(i, 50);
    }


    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(major_arr[i][j]));
            major_matrix_table->setItem(i, j, itm);
        }
    }

}
