#include <QThread>
#include "updateManager.h"
#include "chart.h"
#include "../backend/MySystemInfo.h"
#include <iostream>


void UpdateManager::update()
{
    int interval = 500;
    MySysInfo sysInfo;

    while (updateInProgress)
    {
        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
        sysInfo = SystemRessource::getRessourceFomSysInfo(std::move(sysInfo));
        emit updateMemory((sysInfo.totalMemory - sysInfo.availableMemory) / kiloBytes_to_gigaBytes);
        sysInfo = SystemRessource::getCPUSage(std::move(sysInfo));
        emit updateCPU(sysInfo.cpuUsagePercent);
        emit updateIO(sysInfo.cpuIowait);
        sysInfo = SystemRessource::listProcess(std::move(sysInfo));
        emit updateProcess(std::move(sysInfo));
        std::this_thread::sleep_until(x);
    }
}

void UpdateManager::end()
{
    updateInProgress = false;
}
