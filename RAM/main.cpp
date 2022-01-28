#include <iostream>
#include <unistd.h>
#include "RamReader.h"
#include "Afficheur.h"
#include "CircularBuffer.h"

using namespace std;

int main()
{
    RamReader reader;
    Afficheur afficheur(cout, reader.viewTotale());
    CircularBuffer buffer(10);
    while (true)
    {
        afficheur.afficher(reader.viewUsage());
        sleep(1);
    }
    return 0;
}
