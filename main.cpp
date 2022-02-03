#include <iostream>

#include <chrono>
#include "src/frontend/Affichage.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World from my Task manager!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(1);

    Affichage affichage{};
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

