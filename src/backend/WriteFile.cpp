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
#include <thread>

std::string NowToString()
{

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss{};
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
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

    time_t now = time(nullptr);
    char* date_time = ctime(&now);
    std::string filename = "MySysInfo-" + NowToString();

    write_file_binary(filename, buffer, k);
    std::cout << "Write archive : " << filename << std::endl;

}

MySysInfo WriteFile::readSysInfoFromFile(const std::string& filename) {

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

void WriteFile::startArchive(size_t interval) {
    std::thread([interval]()
        {
            MySysInfo sysInfo = MySysInfo{};
            while (true) {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                sysInfo = SystemRessource::getRessourceFomSysInfo(std::move(sysInfo));
                sysInfo = SystemRessource::getCPUSage(std::move(sysInfo));
                WriteFile::writeSysInfoToFile(sysInfo);
                std::this_thread::sleep_until(x);
            }
        }).detach();
}

