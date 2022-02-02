//
// Created by abeauquel on 01/02/2022.
//

#ifndef IFT611_SYSTEMRESSOURCE_H
#define IFT611_SYSTEMRESSOURCE_H


#include <linux/sysinfo.h>
#include <sys/sysinfo.h>
#include <ostream>


struct MySysInfo{
    __kernel_long_t time;
    double totalVirtualMemory{};
    double usedVirtualMemory{};
    double physicalMemory{};
    double usedPhysicalMemory{};

    MySysInfo();

    friend std::ostream &operator<<(std::ostream &os, const MySysInfo &info);

};

class SystemRessource {
    struct sysinfo memInfo{};
public:
    MySysInfo getSystemInfo();
};


#endif //IFT611_SYSTEMRESSOURCE_H
