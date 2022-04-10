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
        sysInfo = SystemRessource::getCPUSage(std::move(sysInfo));
        emit signal(sysInfo.cpuUsagePercent);

        std::this_thread::sleep_until(x);
    }
    std::cout<<"Done"<<std::endl;
}

void UpdateManager::end()
{
    /*
    mutex.lock();
    updateInProgress =  false;
    mutex.unlock();
    */
    std::cout << "Here" << std::endl;
    updateInProgress = false;
    std::cout<< updateInProgress << std::endl;
}
