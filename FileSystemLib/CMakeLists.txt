cmake_minimum_required(VERSION 3.20)
project(fileSystemLib)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCE_LIB
        "src/*.h"
        "src/*.cpp"
        )
find_library(MAP_LIB libmapTemplate.a
        PATHS ../map/cmake-build-debug/)

add_library(FileSystemLib STATIC ${SOURCE_LIB})
target_include_directories(FileSystemLib PRIVATE ../map/src/)
target_link_libraries(FileSystemLib PRIVATE ${MAP_LIB})