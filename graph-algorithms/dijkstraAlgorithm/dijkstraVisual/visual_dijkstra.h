#ifndef VISUAL_DIJKSTRA_H
#define VISUAL_DIJKSTRA_H

#include <cmath>

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QDebug>
#include <QMap>

namespace Ui {
class VisualDijkstra;
}

class VisualDijkstra : public QWidget
{
    Q_OBJECT

public slots:
    void obPbCreateField();
    void myEventHandler();
    void onPbLaunch();

public:
    explicit VisualDijkstra(QWidget *parent = nullptr);
    ~VisualDijkstra();

    QVector<QVector<int>> play_field_arr;
    uint play_field_arr_size;
    QMap<QTableWidgetItem*, int> pf_map;
    QVector<char> used;
    QVector<int> min_distance;

    QTableWidget *play_field;

    uint start_vertex;
    uint end_vertex;

    void setPlayFieldArray();
    void dijkstraAlgo();

private:
    Ui::VisualDijkstra *ui;
};

#endif // VISUAL_DIJKSTRA_H
