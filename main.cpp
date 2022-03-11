#include <iostream>

#include <chrono>
#include "src/frontend/Affichage.h"
#include <QtWidgets/QtWidgets>
#include "src/frontend/window.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World from my Task manager!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::milliseconds (500);

    Affichage affichage{};
    int i = 0;
    QApplication app(i, nullptr);
    Window window;
    window.show();
    while(true)
    {

        if(std::chrono::steady_clock::now() - start > duration)
        {
            affichage.afficherConsole();
            start= std::chrono::steady_clock::now();
        }
    }

}
#pragma clang diagnostic pop

