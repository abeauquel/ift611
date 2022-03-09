#!/bin/bash
# Install dependency
# CMake
#sudo apt install -y software-properties-common lsb-release
#wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
#sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
#sudo apt update
#sudo apt install kitware-archive-keyring
#sudo apt install cmake
# Online QT
wget https://d13lb3tujbc8s0.cloudfront.net/onlineinstallers/qt-unified-linux-x64-4.3.0-online.run
chmod +x qt-unified-linux-x64-4.3.0-online.run
./qt-unified-linux-x64-4.3.0-online.run

# QT
#sudo apt install -y g++ gdb make ninja-build rsync zip pkg-config libglu1-mesa-dev freeglut3-dev mesa-common-dev libglu1-mesa-dev libdrm-dev libgles2-mesa-dev nodejs 
# Download and build QT library
#wget https://download.qt.io/official_releases/qt/6.2/6.2.3/single/qt-everywhere-src-6.2.3.tar.xz
#tar -xf qt-everywhere-src-6.2.3.tar.xz
#mv qt-everywhere-src-6.2.3.tar.xz QT
#cd QT
#mkdir -p biuld/default
#cd build/default
#cmake -CNinja ../..
#ninja
#cmake --build . --parallel
#cmake --install .
