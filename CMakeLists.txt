# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

#project ("ProjetDeSession")

# Include sub-projects.
#add_subdirectory ("ProjetDeSession")



#cmake_minimum_required(VERSION 3.21)
project(ift611)

set(CMAKE_CXX_STANDARD 20) 

add_executable(ift611
        main.cpp src/backend/SystemRessource.cpp src/backend/SystemRessource.h src/backend/MySystemInfo.cpp src/backend/MySystemInfo.h src/frontend/Affichage.cpp src/frontend/Affichage.h)