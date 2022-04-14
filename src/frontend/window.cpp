#include <QtGui>
#include <QGridLayout>
#include <QTabWidget>
#include <QLabel>
#include <QThread>
#include <QDeadlineTimer>
#include <QScrollArea>
#include <tuple>
#include <chrono>
#include "window.h"
#include "chart.h"
#include "updateManager.h"
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"
#include <iostream>

Window::Window(): systemRessource{}, 
                  mySysInfo{}, 
                  cpuChart{this, "CPU Usage", std::tuple<int, int>(0, 100)}, 
                  memChart{this, "Memory Usage",
                           std::tuple<int, int>(0, (SystemRessource::getRessourceFomSysInfo(MySysInfo{}).totalMemory / kiloBytes_to_gigaBytes))},
                  ioChart{this, "I/O Usage", std::tuple<int, int>(0, 2000)},
                  updateManager{}, 
                  updateThread{this}
{
    createRessourcePage();
    createDetailPage();
    prepareUpdates();
}

void Window::createRessourcePage()
{
    tab = new QTabWidget(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(cpuChart.getChartView(), 0, 0);
    layout->addWidget(memChart.getChartView(), 1, 0);
    layout->addWidget(ioChart.getChartView(), 2, 0);
    auto page = new QWidget(this);
    page->setLayout(layout);
    tab->resize(windowSize, windowSize);
    tab->addTab(page, "Ressource Usage");   
}

void Window::createDetailPage()
{
    detailPage = new QWidget(this);
    detailLayout = new QGridLayout;
    QScrollArea *scroll = new QScrollArea(tab);
    scroll->setWidget(detailPage);
    mySysInfo = SystemRessource::listProcess(mySysInfo);
    if(!mySysInfo.listProcess.empty()){
        createTitleDetailPage(mySysInfo.listProcess[0].time);
       // mySysInfo= addProcessToDetailPage(std::move(mySysInfo));
        detailPage->setLayout(detailLayout);
    }
    scroll->setWidgetResizable(true);
//    QScrollBar *scrollBar = new QScrollBar(Qt::Vertical, detailPage);
//    tab->addTab(detailPage, "Detail");
    tab->addTab(scroll, "Detail");
}

void Window::createTitleDetailPage(const std::string& time)
{
    QLabel *title_pid = new QLabel(tr("PID"));
    QLabel *title_ppid = new QLabel(tr("Name"));
    QLabel *title_cpu_usage = new QLabel(tr("CPU Usage"));
    QLabel *title_mem_usage = new QLabel(tr("Memory Usage"));
    QLabel *title_user_usage = new QLabel(tr("User Usage"));
    QLabel *title_sys_usage = new QLabel(tr("System Usage"));
    auto timeText = "time: " + time;
    QLabel *title_time = new QLabel(timeText.c_str());
    
    detailLayout->addWidget(title_pid, 0, 0);
    detailLayout->addWidget(title_ppid, 0, 1);
    detailLayout->addWidget(title_cpu_usage, 0, 2);
    detailLayout->addWidget(title_mem_usage, 0, 3);
    detailLayout->addWidget(title_user_usage, 0, 4);
    detailLayout->addWidget(title_sys_usage, 0, 5);
    detailLayout->addWidget(title_time, 0, 6);

}

void Window::addProcessToDetailPage(MySysInfo& pmySysInfo)
{
    int row_count = 1;
//    sort(pmySysInfo.listProcess.begin(), pmySysInfo.listProcess.end(), [](const ProcessSysInfo& lhs, const ProcessSysInfo& rhs) {
//        return lhs.cpuUsage > rhs.cpuUsage;
//    });
    for(auto process : pmySysInfo.listProcess)
    {
        QLabel *pid = new QLabel(QString::number(process.pid));
        QLabel *name = new QLabel(process.cmd.c_str());
        QLabel *cpu_usage = new QLabel(process.cpuUsage);
        QLabel *mem_usage = new QLabel(process.memUsage);
        QLabel *user_usage = new QLabel(process.usrUsage);
        QLabel *sys_usage = new QLabel(process.systemUsage);

        detailLayout->addWidget(pid, row_count, 0);
        detailLayout->addWidget(name, row_count, 1);
        detailLayout->addWidget(cpu_usage, row_count, 2);
        detailLayout->addWidget(mem_usage, row_count, 3);
        detailLayout->addWidget(user_usage, row_count, 4);
        detailLayout->addWidget(sys_usage, row_count, 5);
        ++row_count;
    }
}

void Window::updateDetailPage(MySysInfo* pmySysInfo)//todo pass by ref with the signal
{
    QLayoutItem *item;
    while((item = detailLayout->takeAt(0)))
    {
        delete item->widget();
    }
    delete detailLayout;
    detailLayout = new QGridLayout;
    if(!mySysInfo.listProcess.empty()){
        createTitleDetailPage(pmySysInfo->listProcess[0].time);
        addProcessToDetailPage(*pmySysInfo);
        detailPage->setLayout(detailLayout);
    }
}


void Window::prepareUpdates()
{
    updateManager.moveToThread(&updateThread);
    connect(&updateThread, &QThread::finished, &updateManager, &QObject::deleteLater);

    connect(this, &Window::startUpdate, &updateManager, &UpdateManager::update);
    connect(&updateManager, &UpdateManager::updateCPU, &cpuChart, &Chart::addPoint);
    connect(&updateManager, &UpdateManager::updateMemory, &memChart, &Chart::addPoint);
    connect(&updateManager, &UpdateManager::updateIO, &ioChart, &Chart::addPoint);
    connect(&updateManager, &UpdateManager::updateProcess, this, &Window::updateDetailPage);
    updateThread.start();
    emit startUpdate();
}

Window::~Window()
{   
    updateManager.end();
    updateThread.wait();
    updateThread.quit();
}
