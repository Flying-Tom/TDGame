cmake_minimum_required(VERSION 3.10)
project(TDGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE CMAKE_CXX_SOURCES src/*.cpp)
file(GLOB_RECURSE CMAKE_CXX_HEADERS include/*.h)
file(GLOB CMAKE_CXX_RESOURCES resource/*.qrc)

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Multimedia)

# Platform-specific executable definition
if(WIN32)
  message(STATUS "Compiling for Windows")
  add_executable(TDGame WIN32
    ${CMAKE_CXX_HEADERS}
    ${CMAKE_CXX_SOURCES}
    ${CMAKE_CXX_RESOURCES}
  )
elseif(APPLE)
  message(STATUS "Compiling for macOS")

  # Optional: bundle the app
  set(MACOSX_BUNDLE_ICON_FILE icon.icns) # Optional
  set_source_files_properties(${CMAKE_CXX_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
  add_executable(TDGame MACOSX_BUNDLE
    ${CMAKE_CXX_HEADERS}
    ${CMAKE_CXX_SOURCES}
    ${CMAKE_CXX_RESOURCES}
  )
else()
  message(STATUS "Compiling for Unix/Linux")
  add_executable(TDGame
    ${CMAKE_CXX_HEADERS}
    ${CMAKE_CXX_SOURCES}
    ${CMAKE_CXX_RESOURCES}
  )
endif()

# Link Qt libraries
target_link_libraries(TDGame Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Multimedia)
