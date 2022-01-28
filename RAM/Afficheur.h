#ifndef AFFICHEUR_H
#define AFFICHEUR_H
#include <iostream>
#include <cstddef>
#include "CircularBuffer.h"

class Afficheur
{
private:
    const int B_IN_GB = 1000000000;
    const int BORDER = 2;
    const std::size_t HISTORY_SIZE = 10;
    unsigned long totalRam;
    std::ostream& ostream;
    CircularBuffer *buffer;
    int graphHeight, outputHeight, outputWidth;
    char** output;

public:
    Afficheur(std::ostream&, const unsigned long);
    void afficher(const unsigned long);
    ~Afficheur();

private:
    void addUsage(const unsigned long);
    void drawGraph() const;
    void createBorder() const;
    void generateOutput() const;
    void drawOutput() const;

};

#endif // AFFICHEUR_H
