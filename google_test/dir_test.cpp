#include "Dir.h"
#include "gtest/gtest.h"
#include "FileSystem.h"

TEST(Constructors, TestHierarchy) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    System::FileSystem sys(associatedFile);

    sys.getRootDir();
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}