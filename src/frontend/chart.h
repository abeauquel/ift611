#ifndef CHART_H
#define CHART_H

#include <QSplineSeries>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <tuple>
#include <QWidget>
//#include "../backend/MySystemInfo.h"

class Chart : public QWidget 
{

    Q_OBJECT

public slots:
    void addPoint(double);

public:
    Chart(QWidget *parent, const char* title, double initialPoint, std::tuple<int, int> vertialAxisRange);
    QWidget* getChartView() { return chartView; }

private:   
    enum { pointInsertPosition = 10 };
    QSplineSeries *series;
    QChart *chart;
    QChartView *chartView;
};


#endif
