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
private:
    struct sysinfo memInfo{};
    void getRessourceFomSysInfo(MySysInfo &mySysInfo);
public:
    MySysInfo getSystemInfo();
};


#endif //IFT611_SYSTEMRESSOURCE_H
