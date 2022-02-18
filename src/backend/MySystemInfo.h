//
// Created by abeauquel on 03/02/2022.
//

#ifndef IFT611_MYSYSTEMINFO_H
#define IFT611_MYSYSTEMINFO_H
#include <ostream>


struct MySysInfo{
    long time{};
    double totalVirtualMemory{};
    double usedVirtualMemory{};
    double physicalMemory{};
    double usedPhysicalMemory{};
    double cpuUsagePercent{};
    unsigned long long totalUser{};
    unsigned long long totalUserLow{};
    unsigned long long totalSys{};
    unsigned long long totalIdle{};
    MySysInfo();

    friend std::ostream &operator<<(std::ostream &os, const MySysInfo &info);

};

#endif //IFT611_MYSYSTEMINFO_H
