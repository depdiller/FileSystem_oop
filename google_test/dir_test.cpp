#include "Dir.h"
#include "gtest/gtest.h"
#include "FileSystem.h"

TEST(Constructors, TestHierarchy) {
    System::Dir dir(1, 66);

}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}