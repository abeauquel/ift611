//
// Created by abeauquel on 03/02/2022.
//

#ifndef IFT611_AFFICHAGE_H
#define IFT611_AFFICHAGE_H

#include "../backend/MySystemInfo.h"
#include "../backend/SystemRessource.h"
#include "../backend/WriteFile.h"
#include <iostream>

class Affichage {
    SystemRessource systemRessource{};

public:
    void afficherConsole();
};


#endif //IFT611_AFFICHAGE_H
