cmake_minimum_required(VERSION 3.10.0)
project(TDGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(include)
file(GLOB CMAKE_CXX_SOURCES src/*.cpp src/**/*.cpp)
file(GLOB CMAKE_CXX_HEADERS include/*.h include/**/*.h)
file(GLOB CMAKE_CXX_RESOURCES resource/*.qrc)

find_package(Qt5 COMPONENTS Widgets Core Gui Multimedia REQUIRED)

if(WIN32)
message(status "compiling for win32")
    add_executable(TDGame WIN32
    ${CMAKE_CXX_HEADERS}
    ${CMAKE_CXX_SOURCES}
    ${CMAKE_CXX_RESOURCES}
    )
else()
    add_executable(TDGame 
    ${CMAKE_CXX_HEADERS}
    ${CMAKE_CXX_SOURCES}
    ${CMAKE_CXX_RESOURCES}
    )
endif()
target_link_libraries(TDGame Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Multimedia)

