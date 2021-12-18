cmake_minimum_required(VERSION 3.20)
project(FileSystem)

set(CMAKE_CXX_STANDARD 14)

#include_directories(FileSystemLib/src)

add_subdirectory(FileSystemLib)

add_executable(FileSystem main.cpp)
target_include_directories(FileSystem PRIVATE FileSystemLib/src)
target_link_libraries(FileSystem PUBLIC FileSystemLib)