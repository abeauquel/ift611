#include <iostream>

#include <chrono>
#include "src/frontend/window.h"
#include "src/backend/MySystemInfo.h"
#include "src/backend/SystemRessource.h"
#include <assert.h>
#include "src/backend/WriteFile.h"
#include <unistd.h>
#include <thread>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

void stress() {
    system("stress --cpu 100");
}

void task1(std::string msg)
{
    std::cout << "task1 says: " << msg;
}


int main() {
    //Varibale de départ
    auto duration = std::chrono::milliseconds(500);
    SystemRessource systemRessource{};
    MySysInfo sysInfo = MySysInfo{};
    std::atomic<short> idSysInfo;

    int nbIter = 1000;

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto timeMin = std::chrono::duration_cast<std::chrono::nanoseconds>(end - end);
    auto timeMax = std::chrono::duration_cast<std::chrono::nanoseconds>(end - end);
    auto timeAverage = std::chrono::duration_cast<std::chrono::nanoseconds>(end - end);
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - end);
    auto timeTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(end - end);

    auto debut = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nbIter; i++) {

        //delete &sysInfo;
        sysInfo = MySysInfo{};

        //std::thread t1(task1, "Hello");

        //TEST MySysInfo
        start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::getRessourceFomSysInfo(std::move(sysInfo));     //getRessourceFomSysInfo
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        timeTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(time);
        std::cout << "getRessourceFomSysInfo Duration: " << time.count() << " ns\n";
        start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::getCPUSage(std::move(sysInfo));       //getCPUsage
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        timeTotal = std::chrono::duration_cast<std::chrono::nanoseconds>(timeTotal + time);
        std::cout << "getCPUSage Duration: " << time.count() << " ns\n";
        
        timeAverage = std::chrono::duration_cast<std::chrono::nanoseconds>(timeTotal + timeAverage);
        if (i == 1) {
             timeMin = std::chrono::duration_cast<std::chrono::nanoseconds>(timeTotal);
             timeMax = std::chrono::duration_cast<std::chrono::nanoseconds>(timeTotal);
        }
        else {
            if (timeMin > timeTotal) {
                timeMin = timeTotal;
            }
            if (timeMax < timeTotal) {
                timeMax = timeTotal;
            }
        }


        //TEST writeFile
        start = std::chrono::high_resolution_clock::now();
        WriteFile::writeSysInfoToFile(sysInfo);
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "WriteFile Duration: " << time.count() << " ns\n";


        //TEST readFile
        char* buffer = static_cast<char*>(static_cast<void*>(&sysInfo));
        std::string filename = "test";
        int k = sizeof(MySysInfo);
        WriteFile::write_file_binary(filename, buffer, k);
        start = std::chrono::high_resolution_clock::now();
        auto mySysInfoReaded = WriteFile::readSysInfoFromFile(filename);
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "ReadFile Duration: " << time.count() << " ns\n";


        //Test que la lecture retrouve les bonnes données
        assert(sysInfo.availableMemory == mySysInfoReaded.availableMemory);
        assert(sysInfo.cpuIowait == mySysInfoReaded.cpuIowait);
        assert(sysInfo.cpuNiceProcess == mySysInfoReaded.cpuNiceProcess);
        assert(sysInfo.cpuSoftIrq == mySysInfoReaded.cpuSoftIrq);
        assert(sysInfo.cpuSystemProcess == mySysInfoReaded.cpuSystemProcess);
        //assert(sysInfo.cpuUsagePercent == mySysInfoReaded.cpuUsagePercent);
        assert(sysInfo.cpuUserProcess == mySysInfoReaded.cpuUserProcess);
        assert(sysInfo.freeMemory == mySysInfoReaded.freeMemory);
        //assert(sysInfo.listProcess == mySysInfoReaded.listProcess);
        assert(sysInfo.time == mySysInfoReaded.time);
        assert(sysInfo.totalMemory == mySysInfoReaded.totalMemory);

        sleep(5);

        std::cout << sysInfo.cpuUsagePercent << "\n";

        

        /*start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::listProcess(std::move(sysInfo));          //listProcess
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        /*std::cout << "listProcess Duration: " << time.count() << " ns\n";
        start = std::chrono::high_resolution_clock::now();
        //idSysInfo.store(2);
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "idSysInfo.store Duration: " << time.count() << " ns\n";*/
    }
    auto fin = std::chrono::high_resolution_clock::now();
    auto temp = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - debut);
    std::cout << "Total Duration: " << temp.count() << " ns\n";

    std::cout << "Temp d'execution Minimal: " << timeMin.count() << " ns\n";
    std::cout << "Temp d'execution Maximal: " << timeMax.count() << " ns\n";
    std::cout << "Temp Total d'execution moyen: " << timeAverage.count()/nbIter << " ns\n";

}

#pragma clang diagnostic  pop
