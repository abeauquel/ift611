#include <iostream>

#include "sys/types.h"
#include "sys/sysinfo.h"

#include <iostream>
#include <chrono>

struct sysinfo memInfo;


void fun()
{
    std::cout<<"RAM usage"<< std::endl;
//    sysinfo (&memInfo);
//    long long totalVirtualMem = memInfo.totalram;
////Add other values in next statement to avoid int overflow on right hand side...
//    totalVirtualMem += memInfo.totalswap;
//    totalVirtualMem *= memInfo.mem_unit;
//
//    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
////Add other values in next statement to avoid int overflow on right hand side...
//    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
//    virtualMemUsed *= memInfo.mem_unit;
}


int main() {

    const int milli_seconds=1000;

    std::cout << "Hello World!\n";


    auto start= std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(1);
    while(1)
    {

        if(std::chrono::steady_clock::now() - start > duration)
        {
            fun();
            start= std::chrono::steady_clock::now();
        }
    }

}

