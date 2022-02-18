//
// Created by abeauquel on 01/02/2022.
//

#include "SystemRessource.h"
#include "MySystemInfo.h"


MySysInfo SystemRessource::getSystemInfo() {
    MySysInfo mySysInfo{};
    getRessourceFomSysInfo(mySysInfo);
    getCPUSage(mySysInfo);
    //todo getRessource from other function or source



    return mySysInfo;
}

void SystemRessource::getRessourceFomSysInfo(MySysInfo &mySysInfo) {

    sysinfo(&memInfo);

    unsigned long long totalVirtualMem = memInfo.totalram;
//Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    unsigned long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
//Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;

    long long totalPhysMem = memInfo.totalram;
//Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;

    long long physMemUsed = memInfo.totalram - memInfo.freeram;
//Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;

    mySysInfo.time = memInfo.uptime;
    mySysInfo.totalVirtualMemory = totalVirtualMem / 1024 * 1e-6;
    mySysInfo.usedVirtualMemory = virtualMemUsed / 1024 * 1e-6;
    mySysInfo.physicalMemory = totalPhysMem / 1024 * 1e-6;
    mySysInfo.usedPhysicalMemory = physMemUsed / 1024 * 1e-6;

}

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;


void SystemRessource::getCPUSage(MySysInfo &mySysInfo){
    double percent;
//     = fopen("/proc/stat", "r");
//    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
//           &lastTotalSys, &lastTotalIdle);
//    fclose(file);
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
           &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                (totalSys - lastTotalSys);
        percent = static_cast<double>(total);
        total += (totalIdle - lastTotalIdle);
        percent /= static_cast<double>(total);
        percent *= 100;
    }

    mySysInfo.totalUser = totalUser;
    mySysInfo.totalUserLow = totalUserLow;
    mySysInfo.totalSys = totalSys;
    mySysInfo.totalIdle = totalIdle;
    mySysInfo.cpuUsagePercent = percent;
}




