cmake_minimum_required(VERSION 3.20)
project(FileSystem)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(FileSystemLib)
#add_subdirectory(google_test)
add_executable(FileSystem main.cpp google_test/fileSystem_test.cpp)
target_link_libraries(FileSystem PUBLIC FileSystemLib)