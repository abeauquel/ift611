#include <QtGui>
#include <QGridLayout>
#include <QTabWidget>
#include <QLabel>
#include <QThread>
#include <QDeadlineTimer>
#include <tuple>
#include <chrono>
#include "window.h"
#include "chart.h"
#include "updateManager.h"
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"

Window::Window(): systemRessource{}, mySysInfo{}, cpuChart{this, "CPU Usage", 10.0, std::tuple<int, int>(0, 100)}, updateManager{}, updateThread{this}
{
    createRessourcePage();
    createDetailPage();
    prepareUpdates();
}

void Window::createRessourcePage()
{
    tab = new QTabWidget(this);
    cpuChart.addPoint(30.4);
    cpuChart.addPoint(5.1);
    cpuChart.addPoint(50);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(cpuChart.getChartView(), 0, 0);
    auto page = new QWidget(this);
    page->setLayout(layout);
    tab->resize(windowSize, windowSize);
    tab->addTab(page, "Ressource Usage");   
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

void Window::prepareUpdates()
{
    updateManager.moveToThread(&updateThread);
    connect(&updateThread, &QThread::finished, &updateManager, &QObject::deleteLater);

    connect(this, &Window::startUpdate, &updateManager, &UpdateManager::update);
    connect(&updateManager, &UpdateManager::signal, &cpuChart, &Chart::addPoint);
    updateThread.start();
//    updateManager.start();
    emit startUpdate();
}

Window::~Window()
{   
    updateManager.end();
//    updateManager.wait();
//    updateManager.quit();
    //updateThread.requestInterruption();
    updateThread.wait();
    updateThread.quit();
/*
    if(!updateThread.wait(1000))
    {
        updateThread.terminate();
    }
    updateThread.exit();
*/
}


