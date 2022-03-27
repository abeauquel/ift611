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

Chart cpuChart = Chart("CPU Usage", 10 * 100, std::tuple<int, int>(0, 100));
Chart memChart("Memory Usage", 1000, std::tuple<int, int>(0, 160000));
SystemRessource systemRessource;

Window::Window() 
{

    MySysInfo mySysInfo = systemRessource.getSystemInfo();
//    std::cout<< mySysInfo.cpuUsagePercent << std::endl;
    cpuChart = Chart("CPU Usage", mySysInfo.cpuUsagePercent * 100, std::tuple<int, int>(0, 100));
    memChart = Chart("Memory Usage", mySysInfo.totalMemory - mySysInfo.availableMemory, std::tuple<int, int>(0, mySysInfo.totalMemory));
    QGridLayout *layout = new QGridLayout;
//    chart.addPoint(50);
//    Chart chart1(title, initialPoint, verticalAxisRange);
//    Chart chart2(title, initialPoint, verticalAxisRange);
    layout->addWidget(cpuChart.getChartView(), 0, 0);
    layout->addWidget(memChart.getChartView(), 1, 0);
//    layout->addWidget(chart2.getChartView(), 2, 0);
    setLayout(layout);
    int interval = 500;
    std::thread([interval]()
                {
                    while (true)
                    {
                        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                        MySysInfo mySysInfo = systemRessource.getSystemInfo();
                        cpuChart.addPoint(mySysInfo.cpuUsagePercent * 100);
                        memChart.addPoint(mySysInfo.totalMemory - mySysInfo.availableMemory);
                        std::this_thread::sleep_until(x);
                    }
                }).detach();
}

void Window::update(Chart chart)
{
    chart.addPoint(30);
}
