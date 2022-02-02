#include <iostream>

#include "sys/types.h"
#include "sys/sysinfo.h"

#include <iostream>
#include <chrono>

struct sysinfo memInfo;


void getRamUse()
{

    sysinfo (&memInfo);
    long long totalVirtualMem = memInfo.totalram;
//Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit  * 0.000001 * 0.001;

    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
//Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit * 0.000001 * 0.001;

    std::cout<<"RAM usage : "
            << " totalVirtualMem : " << totalVirtualMem << " gb"
            << " virtualMemUsed : " << virtualMemUsed << " gb"
            << " free memory : " << totalVirtualMem - virtualMemUsed << " gb"
    << std::endl;
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
            getRamUse();
            start= std::chrono::steady_clock::now();
        }
    }

}

