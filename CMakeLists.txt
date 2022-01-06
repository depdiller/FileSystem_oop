cmake_minimum_required(VERSION 3.20)
project(FileSystem)
set(CMAKE_CXX_STANDARD 23)

find_library(FILE_SYSTEM libFileSystemLib.a
        PATHS ./FileSystemLib/cmake-build-debug/)

add_executable(FileSystem main.cpp)
target_include_directories(FileSystem PRIVATE FileSystemLib/src/)
target_include_directories(FileSystem PRIVATE map/src)
target_link_libraries(FileSystem PRIVATE ${FILE_SYSTEM})