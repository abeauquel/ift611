//
// Created by abeauquel on 03/02/2022.
//

#include "Affichage.h"

void Affichage::afficherConsole() {
    MySysInfo mySysInfo = systemRessource.getSystemInfo();

    std::cout << mySysInfo << std::endl;
}
