include_directories(src)
add_library(FileSystemLib
        src/AbstractFile.h src/AbstractFile.cpp
        src/Descriptor.h src/Descriptor.cpp
        src/Dir.h src/Dir.cpp
        src/EncryptFile.h src/EncryptFile.cpp
        src/File.h src/File.cpp
        src/FileSystem.h src/FileSystem.cpp
        src/User.h src/User.cpp
        src/Permissions.h src/Permissions.cpp)