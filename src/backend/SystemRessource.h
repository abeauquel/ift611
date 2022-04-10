//
// Created by abeauquel on 01/02/2022.
//

#ifndef IFT611_SYSTEMRESSOURCE_H
#define IFT611_SYSTEMRESSOURCE_H


#include <linux/sysinfo.h>
#include <sys/sysinfo.h>
#include <ostream>
#include <atomic>
#include "MySystemInfo.h"


class SystemRessource {
private:
public:
    static MySysInfo getRessourceFomSysInfo(MySysInfo pSysInfo);
    static MySysInfo getCPUSage(MySysInfo pSysInfo);
    static MySysInfo listProcess(MySysInfo pSysInfo);
};


#endif //IFT611_SYSTEMRESSOURCE_H
