#include <iostream>

#include <chrono>
#include "src/frontend/window.h"
#include "src/backend/MySystemInfo.h"
#include "src/backend/SystemRessource.h"
#include <assert.h>
#include "src/backend/WriteFile.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    //Varibale de départ
    auto duration = std::chrono::milliseconds(500);
    SystemRessource systemRessource{};
    MySysInfo sysInfo = MySysInfo{};
    std::atomic<short> idSysInfo;

    auto debut = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {

        MySysInfo sysInfo = MySysInfo{};

        //TEST MySysInfo
        auto start1 = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::getRessourceFomSysInfo(std::move(sysInfo));
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "getRessourceFomSysInfo Duration: " << time.count() << " ns\n";
        start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::getCPUSage(std::move(sysInfo));
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "getCPUSage Duration: " << time.count() << " ns\n";
        start = std::chrono::high_resolution_clock::now();
        sysInfo = SystemRessource::listProcess(std::move(sysInfo));
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "listProcess Duration: " << time.count() << " ns\n";
        start = std::chrono::high_resolution_clock::now();
        idSysInfo.store(2);
        end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "idSysInfo.store Duration: " << time.count() << " ns\n";


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
        assert(sysInfo.cpuUsagePercent == mySysInfoReaded.cpuUsagePercent);
        assert(sysInfo.cpuUserProcess == mySysInfoReaded.cpuUserProcess);
        assert(sysInfo.freeMemory == mySysInfoReaded.freeMemory);
        //assert(sysInfo.listProcess == mySysInfoReaded.listProcess);
        assert(sysInfo.time == mySysInfoReaded.time);
        assert(sysInfo.totalMemory == mySysInfoReaded.totalMemory);

    }
    auto fin = std::chrono::high_resolution_clock::now();
    auto temp = std::chrono::duration_cast<std::chrono::nanoseconds>(fin - debut);
    std::cout << "Total Duration: " << temp.count() << " ns\n";

    //MySysInfo mySysInfo = systemRessource.getSystemInfo();

    /*system("stress --cpu 100");
    std::cout << "pas coince";
    mySysInfo = systemRessource.getSystemInfo();*/

}
#pragma clang diagnostic  pop
