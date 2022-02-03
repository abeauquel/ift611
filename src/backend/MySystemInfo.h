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

    MySysInfo();

    friend std::ostream &operator<<(std::ostream &os, const MySysInfo &info);
};

#endif //IFT611_MYSYSTEMINFO_H
