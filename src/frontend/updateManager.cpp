#include <QThread>
#include "updateManager.h"
#include "chart.h"
#include "../backend/MySystemInfo.h"
#include <iostream>


void UpdateManager::update()
{
    int interval = 1000;
    float testcpu = 35.6;
    size_t testMem = 8000;
//    chart->addPoint(100.0);
    emit signal(100.0);

    while (updateInProgress)
    {
        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
        //testcpu+= 1.0;
        //testMem += 100;
        MySysInfo sysInfo = systemRessource.getSystemInfo(); 
        emit signal(sysInfo.cpuUsagePercent);  
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
