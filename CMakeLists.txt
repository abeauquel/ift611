cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ift611)

list(APPEND CMAKE_PREFIX_PATH "/opt/Qt/6.2.4/gcc_64/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

set(executable "ift611")
set(FRONTEND src/frontend)
file(GLOB BACKEND_SRC
        "src/backend/*.h"
        "src/backend/*.cpp"
        )
set(SOURCE ${FRONTEND}/application.cpp ${FRONTEND}/chart.cpp ${FRONTEND}/window.cpp)
add_executable(${executable} main.cpp ${SOURCE} ${BACKEND_SRC})


#file(GLOB FRONTEND_SRC
#        "src/frontend/*.h"
#        "src/frontend/*.cpp"
#        )
#file(GLOB BACKEND_SRC
#        "src/backend/*.h"
#        "src/backend/*.cpp"
#        )
#add_executable(${executable} main.cpp ${BACKEND_SRC} ${FRONTEND_SRC})

target_link_libraries(ift611 PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Charts)
