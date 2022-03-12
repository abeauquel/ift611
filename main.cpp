#include <iostream>
#include "src/backend/file_write.h"
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

void writeSysInfoToFile(MySysInfo info) {

    int k = sizeof(MySysInfo);
    char* buffer = static_cast<char*>(static_cast<void*>(&info));

    write_file_binary("test.bin", buffer, k);
}

MySysInfo readSysInfoFromFile(std::string filename) {

    MySysInfo result;
    int k = sizeof(MySysInfo);

    std::ifstream file("test.bin", std::ios::binary | std::ios::ate);
    if (!file) {
        std::cout << "Cannot open file!" << std::endl;
        return result;
    }
    file.seekg(0, std::ios::beg);

    file.read((char*)&result, k);

    return result;
}

int main() {

    const int milli_seconds=1000;

    writefile file;
    
    //un exemple d'info-------------
    auto info = new MySysInfo();
    auto result = new MySysInfo();
    info->time = 2000;
    info->totalVirtualMemory = 3000;
    info->usedPhysicalMemory = 3300;
    info->physicalMemory = 4000;
    info->usedPhysicalMemory = 5000;
    info->cpuUsagePercent = 6000;
    info->totalUser = 7000;
    info->totalUserLow = 7100;
    info->totalSys = 7200;
    info->totalIdle = 7300;
    //------------------------------
     
    file.writeSysInfoToFile(*info);

    *result = file.readSysInfoFromFile("test.bin");
    
    std::cout << "Hello World from my Task manager!\n";


    auto start= std::chrono::steady_clock::now(); 
    auto duration = std::chrono::seconds(1);

    Affichage affichage{};
    while(true)
    {

        if(std::chrono::steady_clock::now() - start > duration)
        {
            auto start = std::chrono::steady_clock::now();
            //writeSysInfoToFile(*info);   //Écriture légère <0 ms
            affichage.afficherConsole();
            start= std::chrono::steady_clock::now();
            //*result = readSysInfoFromFile("test.bin"); //Lecture Lourde >15ms
            auto stop = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << duration.count() << std::endl;
        }
    }

}
#pragma clang diagnostic pop

