cmake_minimum_required(VERSION 3.20)
project(Google_test)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_library(FILESYSTEM_LIB libFileSystemLib.a
        PATHS ../cmake-build-debug/FileSystemLib/)

link_libraries(gtest_main ${FILESYSTEM_LIB})
include_directories(../FileSystemLib/src)

add_executable(fileSystem_test fileSystem_test.cpp
        descriptor_test.cpp
        file_test.cpp
        encryptedFile_test.cpp
        permissions_test.cpp
        user_test.cpp
        dir_test.cpp)