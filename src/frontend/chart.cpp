#include "chart.h"
#include <QSplineSeries>
#include <QChart>
#include <QChartView>
#include <tuple>
#include <QPointF>

Chart::Chart(const char* title, float initialPoint, std::tuple<int, int> verticalAxisRange)
{
    series = new QSplineSeries();
 //   series->setName("spline");
    for(int i = 0; i != 9; ++i)
        series->append(i, initialPoint);
    series->append(pointInsertPosition, initialPoint);
/*
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
  */  
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(std::get<0>(verticalAxisRange), std::get<1>(verticalAxisRange));
    chart->axes(Qt::Horizontal).first()->setRange(0, pointInsertPosition); 
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void Chart::addPoint(float newPoint)
{
    series->remove(0);

//    series->append(pointInsertPosition, newPoint);
//    for(QPointF point : series->points())
//    {
//        point.rx()--;
//    }
//    series->

    QSplineSeries *newSeries;
    newSeries = new QSplineSeries();
    for(int i = 0; i != 9; ++i){
        QPointF point = series->at(i);
        newSeries->append(point.x() - 1, point.y());
    }

    newSeries->append(pointInsertPosition, newPoint);
    chart->removeSeries(series);
    chart->addSeries(newSeries);
}
