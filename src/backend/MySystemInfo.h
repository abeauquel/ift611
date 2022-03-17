//
// Created by abeauquel on 03/02/2022.
//

#ifndef IFT611_MYSYSTEMINFO_H
#define IFT611_MYSYSTEMINFO_H
#include <ostream>
#include "vector"

struct ProcessSysInfo{
    char32_t name{};
    double totalVirtualMemory{};
    double usedVirtualMemory{};
    double physicalMemory{};
    double usedPhysicalMemory{};
    double cpuUsagePercent{};
    unsigned long long cpuIowait{};
    unsigned long long cpuUserProcess{};
    unsigned long long cpuNiceProcess{};
    unsigned long long cpuSystemProcess{};
    unsigned long long cpuSoftIrq{};
    ProcessSysInfo();
    friend std::ostream &operator<<(std::ostream &os, const ProcessSysInfo &info);

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
    MySysInfo();
    friend std::ostream &operator<<(std::ostream &os, const MySysInfo &info);
    std::vector<ProcessSysInfo> listProcess;
};

#endif //IFT611_MYSYSTEMINFO_H
