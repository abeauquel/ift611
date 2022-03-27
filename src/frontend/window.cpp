#include <QtGui>
#include "window.h"
#include "chart.h"
#include <QGridLayout>
#include <tuple>
#include <chrono>
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"
#include <iostream>
#include <thread>

//Chart *cpuChart;
//Chart *memChart;
SystemRessource systemRessource;

Window::Window() 
{

    MySysInfo mySysInfo = systemRessource.getSystemInfo();
//    std::cout<< mySysInfo.cpuUsagePercent << std::endl;
    Chart cpuChart = Chart("CPU Usage", mySysInfo.cpuUsagePercent, std::tuple<int, int>(0, 100));
    Chart memChart = Chart("Memory Usage", mySysInfo.totalMemory - mySysInfo.availableMemory, std::tuple<int, int>(0, mySysInfo.totalMemory));
    QGridLayout *layout = new QGridLayout;
//    chart.addPoint(50);
//    Chart chart1(title, initialPoint, verticalAxisRange);
//    Chart chart2(title, initialPoint, verticalAxisRange);
    layout->addWidget(cpuChart.getChartView(), 0, 0);
    layout->addWidget(memChart.getChartView(), 1, 0);
//    layout->addWidget(chart2.getChartView(), 2, 0);
    setLayout(layout);
    int interval = 1000;

   // mySysInfo = systemRessource.getSystemInfo();
//    cpuChart.addPoint(mySysInfo.cpuUsagePercent);
//    memChart.addPoint(mySysInfo.totalMemory - mySysInfo.availableMemory);

    std::thread([interval]()
                {

                    float testcpu = 35.6;
                    size_t testMem = 8000;
                    while (true)
                    {
                        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                        testcpu+= 1.0;
                        testMem += 100;
                        //todo update with new values

                        // todo Fix la methode add point
                        // Passer des references dans la lambda , [interval, &cpuChart, &memChart]
                        // tester :
                        //    cpuChart.addPoint(testcpu);
                        //    memChart.addPoint(testMem);

                        //si ca marche tester :
                        // mySysInfo = systemRessource.getSystemInfo();
                        // cpuChart.addPoint(mySysInfo.cpuUsagePercent);
                        // memChart.addPoint(mySysInfo.totalMemory - mySysInfo.availableMemory);
                        std::this_thread::sleep_until(x);
                    }
                }).detach();
}

void Window::update(Chart chart)
{
    chart.addPoint(30);
}
