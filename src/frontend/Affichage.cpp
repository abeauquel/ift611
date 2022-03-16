//
// Created by abeauquel on 03/02/2022.
//

#include "Affichage.h"

void Affichage::afficherConsole() {
    MySysInfo mySysInfo = systemRessource.getSystemInfo();
    //WriteFile::writeSysInfoToFile(mySysInfo);
    std::cout << mySysInfo << std::endl;
}
