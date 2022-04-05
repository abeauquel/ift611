#include "chart.h"
#include <QSplineSeries>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <tuple>
#include <QPointF>
#include <iostream>

Chart::Chart(const char* title, float initialPoint, std::tuple<int, int> verticalAxisRange)
{
    series = new QSplineSeries();
    for(int i = 0; i < pointInsertPosition; ++i)
        series->append(i, 5);
    series->append(pointInsertPosition, initialPoint);
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(std::get<0>(verticalAxisRange), std::get<1>(verticalAxisRange));
    chart->axes(Qt::Horizontal).first()->setRange(0, pointInsertPosition); 
    chartView = new QChartView(chart);
}

void Chart::addPoint(float newPoint)
{
    for (int i = 1; i <= pointInsertPosition; ++i)
    {
        QPointF point = series->at(i);
        QPointF toReplace = series->at(i - 1);
        point.setX(toReplace.rx());
        series->replace(toReplace, point);
    }
    //series->remove(pointInsertPosition);
    series->replace(pointInsertPosition, QPointF(pointInsertPosition, newPoint));
}
