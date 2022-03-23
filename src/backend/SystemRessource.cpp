//
// Created by abeauquel on 01/02/2022.
//

#include <fstream>
#include <vector>
#include <numeric>
#include <iostream>
#include "SystemRessource.h"
#include "MySystemInfo.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle, previous_idle_time, previous_total_time;

MySysInfo SystemRessource::getSystemInfo() {
    MySysInfo mySysInfo{};
    //init cpu last usage
    previous_idle_time=0, previous_total_time=0;

    getRessourceFomSysInfo(mySysInfo);
    getCPUSage(mySysInfo);

    listProcess(mySysInfo);

    return mySysInfo;
}

void SystemRessource::getRessourceFomSysInfo(MySysInfo &mySysInfo) {
    std::ifstream proc_meminfo("/proc/meminfo");

    proc_meminfo.ignore(9, ' '); // Skip the 'MemTotal:' prefix.
    proc_meminfo >> mySysInfo.totalMemory;

    proc_meminfo.ignore(13); // skip Kb: + MemFree: text
    proc_meminfo >> mySysInfo.freeMemory;

    proc_meminfo.ignore(18); // skip Kb: + MemAvailable: text
    proc_meminfo >> mySysInfo.availableMemory;

    proc_meminfo.close();
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

//void SystemRessource::listProcess(MySysInfo &mySysInfo){
//
//    int status = std::system("ps -ef >test.txt"); // execute the UNIX command "ls -l >test.txt"
//    std::ifstream file("test.txt");
//    file.ignore(56);// skip first line
//
//    while (!file.eof()) {
//        ProcessSysInfo p = ProcessSysInfo();
//
//        file >> p.user;
//        file >> p.pid;
//        file >> p.ppid;
//        file >> p.c;
//        file >> p.stime;
//        file >> p.tty;
//        file >> p.time;
//        getline(file, p.cmd);
//
//        mySysInfo.listProcess.push_back(p);
//    }
//}

//v2
void SystemRessource::listProcess(MySysInfo &mySysInfo){

    int status = std::system("pidstat -h -r -u -U -v >test.txt"); // execute the UNIX command "ls -l >test.txt"
    std::ifstream file("test.txt");

    //skip first 3 lines
    file.ignore(std::numeric_limits<int>::max(), '\n');
    file.ignore(std::numeric_limits<int>::max(), '\n');
    file.ignore(std::numeric_limits<int>::max(), '\n');

    ProcessSysInfo p = ProcessSysInfo();
    while (file >> p.time) {
        file >> p.user;
        file >> p.pid;
        file >> p.usrUsage;
        file >> p.systemUsage;
        file >> p.guestUsage;
        file >> p.waitUsage;
        file >> p.cpuUsage;
        file >> p.cpuId;
        file >> p.minflts;
        file >> p.majflts;
        file >> p.vsz;
        file >> p.rss;
        file >> p.memUsage;
        file >> p.threadId;
        file >> p.fdnr;
        file >> p.cmd;

        mySysInfo.listProcess.push_back(p);
        p = ProcessSysInfo();
    }
}

