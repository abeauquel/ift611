//
// Created by abeauquel on 03/02/2022.
//

#ifndef IFT611_MYSYSTEMINFO_H
#define IFT611_MYSYSTEMINFO_H
#include <ostream>
#include "vector"

struct ProcessSysInfo{
    friend std::ostream &operator<<(std::ostream &os, const ProcessSysInfo &info);

    std::string user;
    short pid;
    short ppid;
    short c;
    std::string stime;
    std::string tty;

    std::string time; //15:04:24
    std::string cmd;
    char usrUsage[8];
    char systemUsage[8];
    char waitUsage[8];
    char cpuUsage[8];
    char memUsage[8];
    char guestUsage[8];
    short cpuId;
    char minflts[8];
    char majflts[8];
    long vsz;
    long rss;
    short threadId;
    short fdnr;

};

struct MySysInfo{
    long time{};
    double totalVirtualMemory{};
    double usedVirtualMemory{};
    double physicalMemory{};
    double usedPhysicalMemory{};
    size_t freeMemory{};
    size_t availableMemory{};
    size_t totalMemory{};
    double cpuUsagePercent{};
    unsigned long long cpuIowait{};
    unsigned long long cpuUserProcess{};
    unsigned long long cpuNiceProcess{};
    unsigned long long cpuSystemProcess{};
    unsigned long long cpuSoftIrq{};
    friend std::ostream &operator<<(std::ostream &os, const MySysInfo &info);
    std::vector<ProcessSysInfo> listProcess;
};

#endif //IFT611_MYSYSTEMINFO_H
