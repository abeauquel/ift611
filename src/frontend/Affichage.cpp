//
// Created by abeauquel on 03/02/2022.
//

#include "Affichage.h"

void Affichage::afficherConsole() {
    MySysInfo mySysInfo = systemRessource.getSystemInfo();

    std::cout <<
      "time " << mySysInfo.time <<
      " physicalMemory : " << mySysInfo.physicalMemory << " gb " <<
      " usedPhysicalMemory : " << mySysInfo.usedPhysicalMemory << " gb " <<
      " totalVirtualMemory: " << mySysInfo.totalVirtualMemory << " gb " <<
      " usedVirtualMemory: " << mySysInfo.usedVirtualMemory << " gb"
      << std::endl;
}
