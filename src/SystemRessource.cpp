//
// Created by abeauquel on 01/02/2022.
//

#include "SystemRessource.h"


MySysInfo SystemRessource::getSystemInfo() {

    sysinfo(&memInfo);

    float totalram = memInfo.totalram * (unsigned long long)memInfo.mem_unit / 1024 * 1e-6;
    float freeram = memInfo.freeram * (unsigned long long)memInfo.mem_unit / 1024 * 1e-6;

    return {totalram, totalram - freeram};
}

MySysInfo::MySysInfo(float totalMemory, float usedMemory) : totalMemory(totalMemory), usedMemory(usedMemory) {}

std::ostream &operator<<(std::ostream &os, const MySysInfo &info) {
    os << "totalMemory: " << info.totalMemory << " gb " <<
    " usedMemory: " << info.usedMemory << " gb";
    return os;
}
