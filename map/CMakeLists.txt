cmake_minimum_required(VERSION 3.20)
project(mapLib)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_LIB
        "src/*.h"
        "src/*.cpp"
        )

add_library(mapTemplate STATIC ${SOURCE_LIB})