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

add_executable(fileSystem_test fileSystem_test.cpp
        ../FileSystemLib/src/FileSystem.h ../FileSystemLib/src/FileSystem.cpp
        ../FileSystemLib/src/User.h ../FileSystemLib/src/User.cpp
        ../FileSystemLib/src/Dir.cpp ../FileSystemLib/src/Dir.h
        ../FileSystemLib/src/AbstractFile.h ../FileSystemLib/src/AbstractFile.cpp
        ../FileSystemLib/src/Permissions.h ../FileSystemLib/src/Permissions.cpp
        ../FileSystemLib/src/Descriptor.h ../FileSystemLib/src/Descriptor.cpp
        ../FileSystemLib/src/File.cpp ../FileSystemLib/src/File.h
        ../FileSystemLib/src/EncryptFile.h ../FileSystemLib/src/EncryptFile.cpp)
target_link_libraries(fileSystem_test gtest_main)