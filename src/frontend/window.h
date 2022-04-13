#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QThread>
#include <QGridLayout>
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
    Chart memChart;
    Chart ioChart;
    SystemRessource systemRessource;
    MySysInfo mySysInfo;
    UpdateManager updateManager;
    QWidget *detailPage;
    QGridLayout *detailLayout;

public:
signals:
    void startUpdate();
    void stopUpdate();

public:
    Window();
    void updateDetailPage(MySysInfo);
    ~Window();
private:
    void prepareUpdates();
    void createRessourcePage();
    void createDetailPage();
    void createTitleDetailPage();
    void addProcessToDetailPage(MySysInfo);
};


#endif
