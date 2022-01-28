#ifndef RAMREADER_H
#define RAMREADER_H
#include <sys/sysinfo.h>


class RamReader
{
public:
    RamReader();
    [[nodiscard]] unsigned long viewUsage() const;
    [[nodiscard]] unsigned long viewTotale() const;

protected:

private:

};

#endif // RAMREADER_H
