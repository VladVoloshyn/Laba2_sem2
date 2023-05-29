#include "visual_dijkstra.h"
#include "ui_visual_dijkstra.h"

VisualDijkstra::VisualDijkstra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualDijkstra)
{
    ui->setupUi(this);


    play_field_arr_size = 16;

    play_field = new QTableWidget();

    min_distance.resize(play_field_arr_size);

    used.resize(play_field_arr_size);

    play_field_arr.resize(play_field_arr_size);
    for (uint i = 0; i < play_field_arr_size; i++) {
        play_field_arr[i].resize(play_field_arr_size);
    }

    connect(ui->pb_create_field, &QPushButton::clicked, this, &VisualDijkstra::obPbCreateField);
    connect(play_field, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(myEventHandler()));
    connect(ui->pb_launch_action, &QPushButton::clicked, this, &VisualDijkstra::onPbLaunch);

}

VisualDijkstra::~VisualDijkstra()
{
    delete ui;
}

void VisualDijkstra::setPlayFieldArray()
{
    for (uint i = 0; i < play_field_arr_size; i++) {
        used[i] = false;
    }

    for (uint i = 0; i < play_field_arr_size; i++) {
        for (uint j = 0; j < play_field_arr_size; j++) {

                play_field_arr[i][j] = INT_MAX;

        }
    }

    for (uint i = 0; i < play_field_arr_size; i++) {
        for (uint j = 0; j < play_field_arr_size; j++) {
            if (i == j) {
                play_field_arr[i][j] = 0;
            }
        }
    }

    play_field_arr[0][1] = 1;
    play_field_arr[0][3] = 1;

    play_field_arr[1][0] = 1;
    play_field_arr[1][2] = 1;
    play_field_arr[1][4] = 1;


    play_field_arr[2][1] = 1;
    play_field_arr[2][3] = 1;
    play_field_arr[2][5] = 1;
    play_field_arr[2][7] = 1;

    play_field_arr[3][0] = 1;
    play_field_arr[3][2] = 1;
    play_field_arr[3][8] = 1;

    play_field_arr[4][1] = 1;
    play_field_arr[4][5] = 1;
    play_field_arr[4][9] = 1;

    play_field_arr[5][2] = 1;
    play_field_arr[5][4] = 1;
    play_field_arr[5][6] = 1;
    play_field_arr[5][10] = 1;

    play_field_arr[6][5] = 1;
    play_field_arr[6][7] = 1;
    play_field_arr[6][11] = 1;
    play_field_arr[6][13] = 1;

    play_field_arr[7][2] = 1;
    play_field_arr[7][6] = 1;
    play_field_arr[7][8] = 1;
    play_field_arr[7][14] = 1;

    play_field_arr[8][3] = 1;
    play_field_arr[8][7] = 1;
    play_field_arr[8][15] = 1;

    play_field_arr[9][4] = 1;
    play_field_arr[9][10] = 1;

    play_field_arr[10][5] = 1;
    play_field_arr[10][9] = 1;
    play_field_arr[10][11] = 1;

    play_field_arr[11][6] = 1;
    play_field_arr[11][10] = 1;
    play_field_arr[11][12] = 1;

    play_field_arr[12][11] = 1;
    play_field_arr[12][13] = 1;

    play_field_arr[13][6] = 1;
    play_field_arr[13][12] = 1;
    play_field_arr[13][14] = 1;

    play_field_arr[14][7] = 1;
    play_field_arr[14][13] = 1;
    play_field_arr[14][15] = 1;

    play_field_arr[15][8] = 1;
    play_field_arr[15][14] = 1;

    pf_map[play_field->item(3, 0)] = 0;
    pf_map[play_field->item(2, 0)] = 1;
    pf_map[play_field->item(2, 1)] = 2;
    pf_map[play_field->item(3, 1)] = 3;
    pf_map[play_field->item(1, 0)] = 4;
    pf_map[play_field->item(1, 1)] = 5;
    pf_map[play_field->item(1, 2)] = 6;
    pf_map[play_field->item(2, 2)] = 7;
    pf_map[play_field->item(3, 2)] = 8;
    pf_map[play_field->item(0, 0)] = 9;
    pf_map[play_field->item(0, 1)] = 10;
    pf_map[play_field->item(0, 2)] = 11;
    pf_map[play_field->item(0, 3)] = 12;
    pf_map[play_field->item(1, 3)] = 13;
    pf_map[play_field->item(2, 3)] = 14;
    pf_map[play_field->item(3, 3)] = 15;

}



void VisualDijkstra::obPbCreateField()
{
    play_field->setColumnCount(4);
    play_field->setRowCount(4);

    for (uint i = 0; i < 4; i++) {
        play_field->setColumnWidth(i, 50);
    }
    for (uint i = 0; i < 4; i++) {
        play_field->setRowHeight(i, 50);
    }

    for (uint i = 0; i < 4; i++) {
        for (uint j = 0; j < 4; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            play_field->setItem(i, j, item);
        }
    }



    setPlayFieldArray();

    ui->verticalLayout_10->addWidget(play_field);

}

void VisualDijkstra::myEventHandler()
{
    int i = play_field->currentRow();
    int j = play_field->currentColumn();

    if(ui->rb_start_point->isChecked()) {
        play_field->item(i, j)->setBackground(Qt::green);
        start_vertex = pf_map.value(play_field->item(i, j));
    }

    if(ui->rb_barrier->isChecked()) {
        play_field->item(i, j)->setBackground(Qt::black);
        int value = pf_map.value(play_field->item(i, j));
        qDebug() << value;
        for (uint i = 0; i < play_field_arr_size; i++) {
            if (play_field_arr[i][value] == 1) {
                play_field_arr[i][value] = INT_MAX;
            }
        }
    }

    if(ui->rb_end_point->isChecked()) {
        play_field->item(i, j)->setBackground(Qt::red);
        end_vertex = pf_map.value(play_field->item(i, j));
    }
}

void VisualDijkstra::dijkstraAlgo()
{


    for(uint i = 0; i < play_field_arr_size; i++) {
        min_distance[i] = play_field_arr[start_vertex][i];
        used[i] = false;
    }

    min_distance[start_vertex]=0;
    int index = 0, u = 0;
    for (uint i = 0; i < play_field_arr_size; i++) {
        int min=INT_MAX;

        for (uint j = 0; j < play_field_arr_size; j++) {
            if (!used[j] && min_distance[j] < min) {
                min=min_distance[j];
                index=j;
            }
        }

        u=index;
        used[u]=true;
        for(uint j = 0; j < play_field_arr_size; j++) {
            if (!used[j] && play_field_arr[u][j] != INT_MAX && min_distance[u] != INT_MAX && (min_distance[u] + play_field_arr[u][j] < min_distance[j])) {

                min_distance[j] = min_distance[u] + play_field_arr[u][j];

            }
        }
    }


    //Восстановление пути
    QVector<int> ver;
    ver.resize(play_field_arr_size); // массив посещенных вершин
    uint end = end_vertex; // индекс конечной вершины
    qDebug() << start_vertex << " :: " << end;

    ver[0] = end; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = min_distance[end]; // вес конечной вершины

    while (end != start_vertex) {

        for (uint i = 0; i < play_field_arr_size; i++) { // просматриваем все вершины
            if (play_field_arr[i][end] != 0 && play_field_arr[i][end] != INT_MAX)   // если связь есть
            {
                int temp = weight - play_field_arr[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == min_distance[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[k] = i; // и записываем ее в массив
                    ++k;
                }
            }
        }
    }

      for (int i = k - 1; i > 0; i--) {
          if ((uint)ver[i] != start_vertex) {
          pf_map.key(ver[i])->setBackground(Qt::blue);
        }
      }

}

void VisualDijkstra::onPbLaunch()
{
    dijkstraAlgo();
}


