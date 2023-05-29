#ifndef DFS_ALGO_WIDGET_H
#define DFS_ALGO_WIDGET_H

#include <QWidget>
#include <QStatusBar>
#include <QDebug>
#include <QTableWidget>
#include <QStack>


namespace Ui {
class DFSAlgoWidget;
}

class DFSAlgoWidget : public QWidget
{
    Q_OBJECT

public slots:
    void onPbApply();
    void onPbLaunch();

public:
    explicit DFSAlgoWidget(QWidget *parent = nullptr);
    ~DFSAlgoWidget();

    QVector<QVector<int>> major_arr;
    QStatusBar *status_bar;
    QStringList size_list;
    QStack<int> stack;
    QVector<char> used;
    QStringList vertex_done_list;

    QTableWidget *adjacency_matrix_table;
    QTableWidget *major_matrix_table;

    int vertex_count;
    int start_vertex;

    void checkFillArray();
    void dfsAlgo(int v);

private:
    Ui::DFSAlgoWidget *ui;
};

#endif // DFS_ALGO_WIDGET_H
