#include_directories(src)
cmake_minimum_required(VERSION 3.20)
project(Lib)

file(GLOB SOURCE_LIB
        "src/*.h"
        "src/*.cpp"
        )

add_library(FileSystemLib STATIC ${SOURCE_LIB})