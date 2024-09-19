cmake_minimum_required(VERSION 3.26)
project(mondelbrot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp
        cint.cpp
        cint.h
        App.cpp
        App.h)
add_executable(mondelbrot ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(mondelbrot sfml-system sfml-window sfml-graphics sfml-audio sfml-network)