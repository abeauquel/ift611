//
// Created by abeauquel on 03/02/2022.
//

#include "MySystemInfo.h"



MySysInfo::MySysInfo() = default;

std::ostream &operator<<(std::ostream &os, const MySysInfo &info) {
    os << "----------------------------------------------------------------------\n"
    << "time: " << info.time << " totalVirtualMemory: " << info.totalVirtualMemory << "\n usedVirtualMemory: "
    << info.usedVirtualMemory << " physicalMemory: " << info.physicalMemory << " usedPhysicalMemory: " << info.usedPhysicalMemory
    << "\n cpuIowait: " << info.cpuIowait
    << "\n cpuUsagePercent: " << info.cpuUsagePercent ;
//    << " totalUser: " << info.totalUser
//    << "\n totalUserLow: " << info.totalUserLow << " totalSys: " << info.totalSys << " totalIdle: " << info.totalIdle;
    return os;
}
