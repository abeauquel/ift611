//
// Created by abeauquel on 01/02/2022.
//

#include <fstream>
#include <vector>
#include <numeric>
#include "SystemRessource.h"
#include "MySystemInfo.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle, previous_idle_time, previous_total_time;

MySysInfo SystemRessource::getSystemInfo() {
    MySysInfo mySysInfo{};
    //init cpu last usage
    previous_idle_time=0, previous_total_time=0;

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


std::vector<size_t> get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool get_cpu_times(size_t &idle_time, size_t &total_time) {

    return true;
}

void SystemRessource::getCPUSage(MySysInfo &mySysInfo){
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 6)
        return;
    size_t idle_time = cpu_times[3];
    long long total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    //for (size_t idle_time, total_time; get_cpu_times(idle_time, total_time); sleep(1)) {
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);


    previous_idle_time = idle_time;
    previous_total_time = total_time;

    mySysInfo.cpuUsagePercent = utilization;
    mySysInfo.cpuUserProcess = cpu_times[0];
    mySysInfo.cpuNiceProcess = cpu_times[1];
    mySysInfo.cpuSystemProcess = cpu_times[2];
    mySysInfo.cpuIowait = cpu_times[4];
    mySysInfo.cpuSoftIrq = cpu_times[5];
}




