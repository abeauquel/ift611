//
// Created by abeauquel on 03/02/2022.
//

#include "MySystemInfo.h"



std::ostream &operator<<(std::ostream &os, const MySysInfo &info) {
    os <<
       "time " << info.time <<
       " physicalMemory : " << info.physicalMemory << " gb " <<
       " usedPhysicalMemory : " << info.usedPhysicalMemory << " gb " <<
       " totalVirtualMemory: " << info.totalVirtualMemory << " gb " <<
       " usedVirtualMemory: " << info.usedVirtualMemory << " gb";
    return os;
}

MySysInfo::MySysInfo() = default;
