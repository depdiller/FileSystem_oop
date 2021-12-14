#include_directories(src)
file(GLOB SOURCE_LIB
        "src/*.h"
        "src/*.cpp"
        )

add_library(FileSystemLib ${SOURCE_LIB})