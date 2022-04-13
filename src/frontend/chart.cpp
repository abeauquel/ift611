#include "chart.h"
#include <QSplineSeries>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <tuple>
#include <QPointF>
#include <iostream>
#include <QWidget>

Chart::Chart(QWidget *parent, const char* title, std::tuple<int, int> verticalAxisRange)
{
    setParent(parent);
    series = new QSplineSeries();
    for(int i = 0; i <= pointInsertPosition; ++i)
        series->append(i, 0);
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(std::get<0>(verticalAxisRange), std::get<1>(verticalAxisRange));
    chart->axes(Qt::Horizontal).first()->setRange(0, pointInsertPosition); 
    chartView = new QChartView(chart);
}

void Chart::addPoint(double newPoint)
{
    for (int i = 1; i <= pointInsertPosition; ++i)
    {
        QPointF point = series->at(i);
        QPointF toReplace = series->at(i - 1);
        point.setX(toReplace.rx());
        series->replace(toReplace, point);
    }
    series->replace(pointInsertPosition, QPointF(pointInsertPosition, newPoint));
}
