//
// Created by abeauquel on 03/02/2022.
//

#include "MySystemInfo.h"



MySysInfo::MySysInfo() = default;

std::ostream &operator<<(std::ostream &os, const MySysInfo &info) {
    os << "----------------------------------------------------------------------\n"
    << "totalMemory: " << info.totalMemory << " freeMemory: " << info.freeMemory << "\n availableMemory: "
    << info.availableMemory
    << "\n cpuIowait: " << info.cpuIowait
    << "\n cpuUsagePercent: " << info.cpuUsagePercent
    << "\n nb Process: " << info.listProcess.size() ;
//    << "\n totalUserLow: " << info.totalUserLow << " totalSys: " << info.totalSys << " totalIdle: " << info.totalIdle;
    return os;
}

std::ostream &operator<<(std::ostream &os, const ProcessSysInfo &info) {
    os << "----------------------------------------------------------------------\n"
       << "process: " << info.name << " totalVirtualMemory: " << info.totalVirtualMemory << "\n usedVirtualMemory: ";

    return os;
}

ProcessSysInfo::ProcessSysInfo() = default;
