QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dfsAlgorithm/dfs_algo_widget.cpp \
    dijkstraAlgorithm/dijkstraMatrix/dijkstra_algo_widget.cpp \
    dijkstraAlgorithm/dijkstraVisual/visual_dijkstra.cpp \
    fordFulkersonAlgorithm/ford_fulkerson_algo_widget.cpp \
    main/main.cpp \
    main/main_window.cpp \
    warshallAlgorithm/warshall_algo_widget.cpp \

HEADERS += \
    dfsAlgorithm/dfs_algo_widget.h \
    dijkstraAlgorithm/dijkstraMatrix/dijkstra_algo_widget.h \
    dijkstraAlgorithm/dijkstraVisual/visual_dijkstra.h \
    fordFulkersonAlgorithm/ford_fulkerson_algo_widget.h \
    main/main_window.h \
    warshallAlgorithm/warshall_algo_widget.h \

FORMS += \
    dfsAlgorithm/dfs_algo_widget.ui \
    dijkstraAlgorithm/dijkstraMatrix/dijkstra_algo_widget.ui \
    dijkstraAlgorithm/dijkstraVisual/visual_dijkstra.ui \
    fordFulkersonAlgorithm/ford_fulkerson_algo_widget.ui \
    main/main_window.ui \
    warshallAlgorithm/warshall_algo_widget.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/DFS.png \
    images/DijkstraMatrix.png \
    images/DijkstraVisual.png \
    images/Warshall.png \
    style.qss

RESOURCES += \
    resources.qrc \
    resources.qrc
