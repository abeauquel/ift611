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
#include <iostream>

Window::Window(): systemRessource{}, 
                  mySysInfo{}, 
                  cpuChart{this, "CPU Usage", std::tuple<int, int>(0, 100)}, 
                  memChart{this, "Memory Usage", std::tuple<int, int>(0, ((SystemRessource::getRessourceFomSysInfo(MySysInfo{}).totalMemory)/1'048'576.0))},
                  ioChart{this, "I/O Usager", std::tuple<int, int>(0, 1000)},
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
    createTitleDetailPage();
    addProcessToDetailPage(SystemRessource::listProcess(MySysInfo{}));
    detailPage->setLayout(detailLayout);
    tab->addTab(detailPage, "Detail");
}

void Window::createTitleDetailPage()
{
    QLabel *title_pid = new QLabel(tr("PID"));
    QLabel *title_ppid = new QLabel(tr("PPID"));
    QLabel *title_user_usage = new QLabel(tr("User Usage"));
    QLabel *title_sys_usage = new QLabel(tr("System Usage"));
    QLabel *title_cpu_usage = new QLabel(tr("CPU Usage"));
    QLabel *title_mem_usage = new QLabel(tr("Memory Usage"));
    
    detailLayout->addWidget(title_pid, 0, 0);
    detailLayout->addWidget(title_ppid, 0, 1);
    detailLayout->addWidget(title_user_usage, 0, 2);
    detailLayout->addWidget(title_sys_usage, 0, 3);
    detailLayout->addWidget(title_cpu_usage, 0, 4);
    detailLayout->addWidget(title_mem_usage, 0, 5);
}

void Window::addProcessToDetailPage(MySysInfo mySysInfo)
{
    int row_count = 1;
    for(auto process : mySysInfo.listProcess)
    {
        QLabel *pid = new QLabel(QString::number(process.pid));
        QLabel *ppid = new QLabel(QString::number(process.ppid));
        QLabel *user_usage = new QLabel(process.usrUsage);
        QLabel *sys_usage = new QLabel(process.systemUsage);
        QLabel *cpu_usage = new QLabel(process.cpuUsage);
        QLabel *mem_usage = new QLabel(process.memUsage);
    
        detailLayout->addWidget(pid, row_count, 0);
        detailLayout->addWidget(ppid, row_count, 1);
        detailLayout->addWidget(user_usage, row_count, 2);
        detailLayout->addWidget(sys_usage, row_count, 3);
        detailLayout->addWidget(cpu_usage, row_count, 4);
        detailLayout->addWidget(mem_usage, row_count, 5);
        ++row_count;
    }
}

void Window::updateDetailPage(MySysInfo mySysInfo)
{
    QLayoutItem *item;
    while((item = detailLayout->takeAt(0)))
    {
        delete item->widget();
    }
    delete detailLayout;
    detailLayout = new QGridLayout;
    createTitleDetailPage();
    addProcessToDetailPage(mySysInfo);
    detailPage->setLayout(detailLayout);
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


