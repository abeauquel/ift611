#include <QtGui>
#include "window.h"
#include "chart.h"
#include <QGridLayout>
#include <tuple>
#include <chrono>
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"
#include <iostream>

Window::Window() 
{
    SystemRessource systemRessource;
    MySysInfo mySysInfo = systemRessource.getSystemInfo();
//    std::cout<< mySysInfo.cpuUsagePercent << std::endl;
    Chart cpuChart("CPU Usage", mySysInfo.cpuUsagePercent * 100, std::tuple<int, int>(0, 100));
    Chart memChart("Memory Usage", mySysInfo.usedVirtualMemory, std::tuple<int, int>(0, mySysInfo.totalVirtualMemory));
    QGridLayout *layout = new QGridLayout;
//    chart.addPoint(50);
//    Chart chart1(title, initialPoint, verticalAxisRange);
//    Chart chart2(title, initialPoint, verticalAxisRange);
    layout->addWidget(cpuChart.getChartView(), 0, 0);
    layout->addWidget(memChart.getChartView(), 1, 0);
//    layout->addWidget(chart2.getChartView(), 2, 0);
    setLayout(layout);
//    std::thread thread(update());
/*
    auto start = std::chrono::steady_clock::now();
    auto duration = std::chrono::milliseconds(500);
    while(true)
    {
        if(std::chrono::steady_clock::now() - start > duration)
        {
            update();
            start = std::chrono::steady_clock::now();
        }
    }
  */  
}

void Window::update(Chart chart)
{
    chart.addPoint(30);
}
