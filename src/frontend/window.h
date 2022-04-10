#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QThread>
#include "chart.h"
#include "updateManager.h"
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"

class Window : public QWidget
{
    Q_OBJECT
    QThread updateThread;

private:
    enum{ windowSize = 800 };
    QTabWidget *tab;
    Chart cpuChart;
    SystemRessource systemRessource;
    MySysInfo mySysInfo;
    UpdateManager updateManager;

public:
signals:
    void startUpdate();
    void stopUpdate();

public:
    Window();
    ~Window();
private:
    void prepareUpdates();
    void createRessourcePage();
    void createDetailPage();
};


#endif
