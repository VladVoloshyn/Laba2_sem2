#include "ford_fulkerson_algo_widget.h"
#include "ui_ford_fulkerson_algo_widget.h"


template <class T> const T& min (const T& a, const T& b) {
  return !(b<a)?a:b;
}

FordFulkersonAlgoWidget::FordFulkersonAlgoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FordFulkersonAlgoWidget)
{
    ui->setupUi(this);

    size_list << "2x2" << "3x3" << "4x4" << "5x5" << "6x6" << "7x7" << "8x8" << "9x9" << "10x10";


    ui->cb_size_selection->addItems(size_list);

    ui->pb_launch->setDisabled(true);


    connect(ui->pb_apply, &QPushButton::clicked, this, &FordFulkersonAlgoWidget::onPbApply);
    connect(ui->pb_launch, &QPushButton::clicked, this, &FordFulkersonAlgoWidget::onPbLaunch);
}




FordFulkersonAlgoWidget::~FordFulkersonAlgoWidget()
{
    delete ui;
}

bool FordFulkersonAlgoWidget::bfs(int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
        // visited
        bool visited[vertex_count];
        memset(visited, 0, sizeof(visited));

        // Create a queue, enqueue source vertex and mark source
        // vertex as visited
        std::queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        // Standard BFS Loop
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < vertex_count; v++) {
                if (visited[v] == false && minor_arr[u][v] > 0) {
                    // If we find a connection to the sink node,
                    // then there is no point in BFS anymore We
                    // just have to set its parent and can return
                    // true
                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        // We didn't reach sink in BFS starting from source, so
        // return false
        return false;
}

int FordFulkersonAlgoWidget::fordFulkerson(int s, int t)
{
    int u, v;

        // Create a residual graph and fill the residual graph
        // with given capacities in the original graph as
        // residual capacities in residual graph

    // Residual graph where rGraph[i][j]
                       // indicates residual capacity of edge
                       // from i to j (if there is an edge. If
                       // rGraph[i][j] is 0, then there is not)
        for (u = 0; u < vertex_count; u++)
            for (v = 0; v < vertex_count; v++)
                minor_arr[u][v] = major_arr[u][v];


        int parent[vertex_count]; // This array is filled by BFS and to
                       // store path

        int max_flow = 0; // There is no flow initially

        // Augment the flow while there is path from source to
        // sink
        while (bfs(s, t, parent)) {
            // Find minimum residual capacity of the edges along
            // the path filled by BFS. Or we can say find the
            // maximum flow through the path found.
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                path_flow = min(path_flow, minor_arr[u][v]);
            }

            // update residual capacities of the edges and
            // reverse edges along the path
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                minor_arr[u][v] -= path_flow;
                minor_arr[v][u] += path_flow;
            }

            // Add path flow to overall flow
            max_flow += path_flow;
        }

        // Return the overall flow
        return max_flow;
}






void FordFulkersonAlgoWidget::onPbApply()
{
    start_vertex = ui->le_vertex_start->text().toInt();
    qDebug() << "Вершина, взятая из поля в onPbApply" << start_vertex;

    vertex_count = ui->cb_size_selection->currentIndex() + 2;


    if (start_vertex) {
        ui->pb_launch->setDisabled(false);
    }

    QList<QWidget *> widgets_left = ui->scrollAreaWidgetContents_3->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

    qDebug() << widgets_left;


    foreach(QWidget * child, widgets_left){
        qDebug() << "Удаление матрицы смежности";
        child->deleteLater();
    }


    vertex_done_list.clear();


    adjacency_matrix_table = new QTableWidget();

    adjacency_matrix_table->setColumnCount(vertex_count);
    adjacency_matrix_table->setRowCount(vertex_count);

    QStringList hlist;
    hlist << "Порядок обхода";

    QStringList list;
    for (uint i = 1; i <= (uint)vertex_count; i ++) {
        list << QString::number(i);
    }
    adjacency_matrix_table->setHorizontalHeaderLabels(list);

    for (uint i = 0; i < (uint)vertex_count; i++) {
        adjacency_matrix_table->setColumnWidth(i, 50);
    }
    for (uint i = 0; i < (uint)vertex_count; i++) {
        adjacency_matrix_table->setRowHeight(i, 50);
    }

    ui->verticalLayout_3->addWidget(adjacency_matrix_table);

}

void FordFulkersonAlgoWidget::checkFillArray() {


        major_arr.resize(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            major_arr[i].resize(vertex_count);
        }

        minor_arr.resize(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            minor_arr[i].resize(vertex_count);
        }





    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {

            major_arr[i][j] = adjacency_matrix_table->item(i, j)->text().toInt();
        }
    }



    qDebug() << major_arr;
}


void FordFulkersonAlgoWidget::onPbLaunch()
{

    checkFillArray();

    start_vertex = ui->le_vertex_start->text().toInt() - 1;

    qDebug() << "Вершина, передаваемая в FordFulkersonAlgo" <<start_vertex;

    end_vertex = ui->le_vertex_end->text().toInt() - 1;
    qDebug() << "Вершина, передаваемая в FordFulkersonAlgo" <<end_vertex;



    int result = fordFulkerson(start_vertex, end_vertex);

    ui->lb_result->setText(QString::number(result));
}

