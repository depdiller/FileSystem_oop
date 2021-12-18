#include <cstdio>
#include "gtest/gtest.h"
#include "FileSystem.h"
#include "Permissions.h"
#include "User.h"

// FileSystem
TEST(Constructor, DefaultConstructor) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "a+");
    System::FileSystem sys = System::FileSystem(associatedFile);
    ASSERT_EQ(sys.getDisk(), associatedFile);
    ASSERT_EQ(sys.getCurrUser().getUserId(), 1);
    ASSERT_EQ(sys.getCurrUser().getName(), "root");
    ASSERT_EQ(sys.getRootDir().getOwner(), 1);
}

TEST(Setters, AllSetters) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "a+");
    System::FileSystem sys = System::FileSystem(associatedFile);
    sys.login("arkmagrive");
    ASSERT_EQ(sys.getCurrUser().getName(), "arkmagrive");
    System::User newUser = System::User("tmp_login");
    sys.setCurrUser(newUser);
    ASSERT_EQ(sys.getCurrUser().getName(), newUser.getName());
}

TEST(Methods, AdditionalMethods) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "a+");
    System::FileSystem sys = System::FileSystem(associatedFile);
    sys.addToTable("login1");
    sys.addToTable("login2");
    ASSERT_EQ(sys.isInTable("login1"), true);
    ASSERT_EQ(sys.isInTable("login2"), true);
    sys.deleteFromTable("login2");
    ASSERT_EQ(sys.isInTable("login2"), false);
}

TEST(Exceptions, AllExceptions) {
    FILE *associatedFile;
    associatedFile = fopen("C:\\doNotExist", "a+");
    EXPECT_ANY_THROW(System::FileSystem sys = System::FileSystem(associatedFile));
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "a+");
    System::FileSystem sys = System::FileSystem(associatedFile);
    EXPECT_ANY_THROW(sys.deleteFromTable("root"));
    EXPECT_ANY_THROW(sys.addToTable("root"));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}