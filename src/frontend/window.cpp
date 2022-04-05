#include <QtGui>
#include "window.h"
#include "chart.h"
#include <QGridLayout>
#include <tuple>
#include <chrono>
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"
#include <iostream>
#include <QTabWidget>
#include <QLabel>

Window::Window() 
{
    SystemRessource systemRessource;
    MySysInfo mySysInfo = systemRessource.getSystemInfo();

//    std::cout<< mySysInfo.cpuUsagePercent << std::endl;
    tab = new QTabWidget(this);
    
    Chart cpuChart("CPU Usage", mySysInfo.cpuUsagePercent * 100, std::tuple<int, int>(0, 100));
//    cpuChart.addPoint(20.0);
    cpuChart.addPoint(30.4);
    cpuChart.addPoint(5.1);
    cpuChart.addPoint(50);
//    Chart memChart("Memory Usage", mySysInfo.usedVirtualMemory, std::tuple<int, int>(0, mySysInfo.totalVirtualMemory));
    QGridLayout *layout = new QGridLayout;
//    chart.addPoint(50);
//    Chart chart1(title, initialPoint, verticalAxisRange);
//    Chart chart2(title, initialPoint, verticalAxisRange);
    layout->addWidget(cpuChart.getChartView(), 0, 0);
  //  layout->addWidget(memChart.getChartView(), 1, 0);
//    layout->addWidget(chart2.getChartView(), 2, 0);
    auto page = new QWidget(this);
    page->setLayout(layout);
    tab->resize(windowSize, windowSize);
    //setLayout(layout);
    tab->addTab(page, "Ressource Usage");
    createDetailPage();
    int interval = 1000;
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

void Window::createDetailPage()
{
    auto page = new QWidget(this);
    QGridLayout *layout = new QGridLayout;

    QLabel *title_name = new QLabel(tr("Processus Name:"));
    QLabel *title_usage = new QLabel(tr("Processus usage:"));

    QLabel *proc_1_name = new QLabel(tr("proc_1"));
    QLabel *proc_1_usage = new QLabel(tr("20%"));

    QLabel *proc_2_name = new QLabel(tr("proc_2"));
    QLabel *proc_2_usage = new QLabel(tr("43%"));

    QLabel *proc_3_name = new QLabel(tr("proc_3"));
    QLabel *proc_3_usage = new QLabel(tr("12%"));

    QLabel *proc_4_name = new QLabel(tr("proc_4"));
    QLabel *proc_4_usage = new QLabel(tr("25%"));

    layout->addWidget(title_name, 0, 0);
    layout->addWidget(title_usage, 0, 1);
    
    layout->addWidget(proc_1_name, 1, 0);
    layout->addWidget(proc_1_usage, 1, 1);

    layout->addWidget(proc_2_name, 2, 0);
    layout->addWidget(proc_2_usage, 2, 1);

    layout->addWidget(proc_3_name, 3, 0);
    layout->addWidget(proc_3_usage, 3, 1);

    layout->addWidget(proc_4_name, 4, 0);
    layout->addWidget(proc_4_usage, 4, 1);
    page->setLayout(layout);
    tab->addTab(page, "Detail");
}

void Window::update(Chart chart)
{
    chart.addPoint(30);
}
