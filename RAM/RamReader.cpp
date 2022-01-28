#include "RamReader.h"
#include <sys/sysinfo.h>

RamReader::RamReader()
{
    //ctor
}

[[nodiscard]] unsigned long RamReader::viewTotale() const
{
    struct sysinfo meminfo;
    sysinfo(&meminfo);
    return meminfo.totalram;

}


[[nodiscard]] unsigned long RamReader::viewUsage() const
{
    struct sysinfo meminfo;
    sysinfo(&meminfo);
    return meminfo.freeram;

}

