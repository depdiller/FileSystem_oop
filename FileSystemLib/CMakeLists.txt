file(GLOB SOURCE_LIB
        "src/*.h"
        "src/*.cpp"
        )

add_library(FileSystemLib STATIC ${SOURCE_LIB})
#SET_TARGET_PROPERTIES(FileSystemLib PROPERTIES
#        IMPORTED_LOCATION ../google_test/lib)