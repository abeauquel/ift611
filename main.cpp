#include <iostream>

#include <chrono>
#include "src/frontend/Affichage.h"
#include <fstream>
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
bool write_file_binary(std::string const& filename,
    char const* data, size_t const bytes)
{
    std::ofstream b_stream(filename.c_str(),
        std::fstream::out | std::fstream::binary);
    if (b_stream)
    {
        b_stream.write(data, bytes);
        return (b_stream.good());
    }
    return false;
}

int main() {

    const int milli_seconds=1000;

    char* buffer = new char[5];
    write_file_binary("test.bin", reinterpret_cast<char const*>(buffer), sizeof(char) * 5);
    delete[] buffer;

    std::ofstream myfile;
    myfile.open("test.bin");

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

