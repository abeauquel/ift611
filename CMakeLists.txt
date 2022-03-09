cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ift611)

list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.2.3/gcc_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(executable "ift611")
set(FRONTEND src/frontend)
set(SOURCE ${FRONTEND}/window.cpp ${FRONTEND}/renderArea.cpp)
add_executable(${executable} main.cpp ${SOURCE})

target_link_libraries(ift611 PRIVATE Qt6::Widgets)
