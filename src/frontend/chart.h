#ifndef CHART_H
#define CHART_H

//#include <QWidget>
#include <QSplineSeries>
#include <QChart>
#include <QChartView>
#include <tuple>

class Chart 
{
public:
    Chart(const char* title, float initialPoint, std::tuple<int, int> vertialAxisRange);
    QWidget* getChartView() { return chartView; }
    void addPoint(float);
private:
    enum { pointInsertPosition = 10 };
    QSplineSeries *series;
    QChart *chart;
    QChartView *chartView;
};


#endif
