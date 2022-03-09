#include <iostream>
#include <chrono>
#include <QtWidgets/QtWidgets>
#include "src/frontend/window.h"

int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World from my Task manager!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(1);
    int i = 0;
    QApplication app(i, nullptr);
    Window window;
    window.show();
/*
    QGraphicsView view;
    view.setWindowTitle("Task Manager");
    view.resize(800, 700);
*/
/*
    QGraphicsScene *scene = new QGraphicsScene(&view);
    scene->setBackgroundBrush(QBrush(QPixmap(":/grid/grid10.png")));
    view.setScene(scene);
    //QGraphicsRectItem *rect =new QGraphicsRectItem(0, 0, 120, 50);
    //scene->addItem(rect);
    //QGraphicsTextItem *text = scene->addText("CPU"); 
*/
 //   view.show();

    return app.exec();
}

