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
#set(FRONTEND src/frontend)
#set(SOURCE ${FRONTEND}/window.cpp ${FRONTEND}/renderArea.cpp)

file(GLOB FRONTEND_SRC
        "src/frontend/*.h"
        "src/frontend/*.cpp"
        )
file(GLOB BACKEND_SRC
        "src/backend/*.h"
        "src/backend/*.cpp"
        )
add_executable(${executable} main.cpp ${BACKEND_SRC} ${FRONTEND_SRC})

target_link_libraries(ift611 PRIVATE Qt6::Widgets)
