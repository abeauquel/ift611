//
// Created by abeauquel on 01/02/2022.
//

#include "SystemRessource.h"


MySysInfo SystemRessource::getSystemInfo() {

    sysinfo(&memInfo);
    unsigned long long totalVirtualMem = memInfo.totalram;
//Add other values in next statement to avoid int overflow on right hand side...
    //totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;

    unsigned long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
//Add other values in next statement to avoid int overflow on right hand side...
    //virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;


    float rTVM = totalVirtualMem * 1e-9 ;
    float rVM = virtualMemUsed * 1e-9 ;

    return {rTVM, rVM};
}

MySysInfo::MySysInfo(float totalMemory, float usedMemory) : totalMemory(totalMemory), usedMemory(usedMemory) {}

std::ostream &operator<<(std::ostream &os, const MySysInfo &info) {
    os << "totalMemory: " << info.totalMemory << " gb " <<
    " usedMemory: " << info.usedMemory << " gb";
    return os;
}
