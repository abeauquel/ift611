#include "Afficheur.h"
#include "CircularBuffer.h"
#include <algorithm>
#include<bits/stdc++.h>

Afficheur::Afficheur(std::ostream& stream, unsigned long totalRam) : ostream{ stream },
    totalRam{ totalRam }, buffer{ new CircularBuffer(HISTORY_SIZE) }, graphHeight{ (totalRam / B_IN_GB + 0.5f) }
{
    outputHeight = graphHeight + BORDER;
    outputWidth = HISTORY_SIZE + BORDER;
    output = new char* [outputHeight];
    for (int i = 0; i < outputHeight; i++) {
        output[i] = new char[outputWidth];
        memset(output[i], ' ', outputWidth * sizeof(char));
    }
}

void Afficheur::afficher(const unsigned long freeRam)
{
    addUsage(freeRam);
    drawGraph();

}

void Afficheur::addUsage(const unsigned long freeRam)
{
    buffer->add(totalRam - freeRam);
}

void Afficheur::drawGraph() const
{
    createBorder();
    generateOutput();
    drawOutput();
}

void Afficheur::createBorder() const
{
    for(int i = 0; i < graphHeight; i++) {
        output[i][0] = '0' + graphHeight - i;
        output[i][1] = '|';
    }

    for (int i = BORDER; i < outputWidth; i++) {
        output[outputHeight - 2][i] = '_';
        output[outputHeight - 1][i] = '0' + i - 2;
    }
}

void Afficheur::generateOutput() const
{
    for (int i = 0; i < buffer->size(); i++) {
        unsigned long element = buffer->operator[](i);
        int elementHeight = element / B_IN_GB;
        output[graphHeight - elementHeight - 1][i + BORDER] = '*';
    }
}

void Afficheur::drawOutput() const
{
    ostream << std::endl;
    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            ostream << output[i][j];
        }
        ostream << std::endl;
    }
}

Afficheur::~Afficheur()
{
    delete buffer;

}
