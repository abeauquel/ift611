#include "file_write.h"
#include "MySystemInfo.h"
#include <iostream>
#include <fstream>
#include <vector>

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

static void writeSysInfoToFile(MySysInfo info) {

    int k = sizeof(MySysInfo);
    char* buffer = static_cast<char*>(static_cast<void*>(&info));

    write_file_binary("test.bin", buffer, k);
}

static MySysInfo readSysInfoFromFile(std::string filename) {

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

