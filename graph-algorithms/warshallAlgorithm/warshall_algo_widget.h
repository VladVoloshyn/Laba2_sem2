#ifndef WARSHALL_ALGO_WIDGET_H
#define WARSHALL_ALGO_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "QDebug"
#include "QStatusBar"
#include "QString"
#include "QVector"

namespace Ui {
class WarshallAlgoWidget;
}

class WarshallAlgoWidget : public QWidget
{
    Q_OBJECT

public slots:
    void onPbApply();
    void onPbLaunch();

public:
    explicit WarshallAlgoWidget(QWidget *parent = nullptr);
    ~WarshallAlgoWidget();

    QVector<QVector<int>> major_arr;
    QVector<QVector<int>> minor_arr;

    QStatusBar *status_bar;
    QStringList size_list;
    QTableWidget *adjacency_matrix_table;
    QTableWidget *major_matrix_table;

    void checkFillArray();
    void warshallAlgo();
    void setResultMatrixTable();

private:
    Ui::WarshallAlgoWidget *ui;
};

#endif // WARSHALL_ALGO_WIDGET_H
