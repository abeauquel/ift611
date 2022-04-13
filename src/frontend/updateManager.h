#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QThread>
#include <atomic>
#include "chart.h"
#include "updateManager.h"
#include "../backend/SystemRessource.h"
#include "../backend/MySystemInfo.h"

class UpdateManager : public QObject
{
    Q_OBJECT
public:
signals:
    void updateCPU(double);
    void updateMemory(double);
    void updateIO(double);
    void updateProcess(MySysInfo);
private:
    SystemRessource systemRessource;
//    UpdateManager updateManager;
    std::atomic<bool> updateInProgress{ true };
public:
    UpdateManager() : systemRessource{} {};
    void update();
    void end();
};

#endif
