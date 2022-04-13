#include "WriteFile.h"
#include "MySystemInfo.h"
#include "SystemRessource.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>  
#include <ctime>   
#include <sstream> 
#include <iomanip> 
#include <string>  

std::string NowToString()
{

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss{};
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S.%f");
    return ss.str();
}

bool WriteFile::write_file_binary(std::string const& filename,
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

void WriteFile::writeSysInfoToFile(MySysInfo info) {

    int k = sizeof(MySysInfo);
    char* buffer = static_cast<char*>(static_cast<void*>(&info));

    time_t now = time(0);
    char* date_time = ctime(&now);
    std::string filename = "MySysInfo-" + NowToString();

    write_file_binary(filename, buffer, k);
}

MySysInfo WriteFile::readSysInfoFromFile(std::string filename) {

    MySysInfo result;
    int k = sizeof(MySysInfo);

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cout << "Cannot open file!" << std::endl;
        return result;
    }
    file.seekg(0, std::ios::beg);

    file.read((char*)&result, k);

    return result;
}

void WriteFile::archive() {
    MySysInfo sysInfo = MySysInfo{};
    SystemRessource systemRessource{};
    while (true) {
        sysInfo = systemRessource.getSystemInfo();
        WriteFile::writeSysInfoToFile(sysInfo);
    }
}

