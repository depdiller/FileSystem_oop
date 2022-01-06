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
        PATHS ../FileSystemLib/cmake-build-debug/)
#find_library(MAP_LIB libmapTemplate.a
#        PATHS ../map/cmake-build-debug/)
link_libraries(gtest_main ${FILESYSTEM_LIB})
include_directories(../FileSystemLib/src)
include_directories(../map/src)

add_executable(fileSystem_test fileSystem_test.cpp)
add_executable(descriptor_test descriptor_test.cpp)
add_executable(file_test file_test.cpp)
add_executable(encryptedFile_test encryptedFile_test.cpp)
add_executable(permissions_test permissions_test.cpp)
add_executable(user_test user_test.cpp)
add_executable(dir_test dir_test.cpp)