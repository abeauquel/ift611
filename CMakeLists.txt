cmake_minimum_required(VERSION 3.21)
project(ift611)

set(CMAKE_CXX_STANDARD 14)

add_executable(ift611
        main.cpp src/backend/SystemRessource.cpp src/backend/SystemRessource.h src/backend/MySystemInfo.cpp src/backend/MySystemInfo.h src/frontend/Affichage.cpp src/frontend/Affichage.h)
