//
// Created by abeauquel on 01/02/2022.
//

#ifndef IFT611_SYSTEMRESSOURCE_H
#define IFT611_SYSTEMRESSOURCE_H


#include <linux/sysinfo.h>
#include <sys/sysinfo.h>
#include <ostream>
#include "MySystemInfo.h"


class SystemRessource {
    struct sysinfo memInfo{};
public:
    MySysInfo getSystemInfo();
};


#endif //IFT611_SYSTEMRESSOURCE_H
