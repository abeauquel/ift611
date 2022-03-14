#include <iostream>

#include <chrono>
#include "src/frontend/Affichage.h"
#include <QtWidgets/QtWidgets>
#include "src/frontend/window.h"
#include "src/backend/MySystemInfo.h"
#include "src/backend/SystemRessource.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World from my Task manager!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::milliseconds (500);
    
    /* 
    SystemRessource systemRessource{};
    MySysInfo mySysInfo = systemRessource.getSystemInfo();
    int i = 0;
    QApplication app(i, nullptr);
    Window window(mySysInfo);
    window.show();
    */

    Affichage affichage{};
    while(true)
    {

        if(std::chrono::steady_clock::now() - start > duration)
        {
            affichage.afficherConsole();
            start= std::chrono::steady_clock::now();
        }
    }
    return app.exec();
}
#pragma clang diagnostic pop

