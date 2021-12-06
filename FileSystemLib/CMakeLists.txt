include_directories(src)
add_library(FileSystemLib src/AbstractFile.cpp src/AbstractFile.h
        src/Descriptor.h
        src/Dir.h
        src/EncryptFile.h
        src/File.h src/File.cpp
        src/FileSystem.h src/FileSystem.cpp
        src/User.h src/User.cpp
        src/Permissions.h src/Permissions.cpp)