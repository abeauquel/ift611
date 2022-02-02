cmake_minimum_required(VERSION 3.21)
project(ift611)

set(CMAKE_CXX_STANDARD 14)

add_executable(ift611
        main.cpp
        Afficheur.cpp Afficheur.h
        CircularBuffer.cpp CircularBuffer.h
        RamReader.cpp RamReader.h)