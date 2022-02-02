#include <iostream>

#include <chrono>
#include "src/SystemRessource.h"

int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(1);

    SystemRessource systemRessource{};
    while(1)
    {

        if(std::chrono::steady_clock::now() - start > duration)
        {
            std::cout << systemRessource.getSystemInfo()  << std::endl;
            start= std::chrono::steady_clock::now();
        }
    }

}

