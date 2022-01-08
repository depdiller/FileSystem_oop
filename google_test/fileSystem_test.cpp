#include <cstdio>
#include "gtest/gtest.h"
#include "FileSystem.h"
#include "Permissions.h"
#include "User.h"

using namespace System;
TEST(Constructor, DefaultConstructor) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");

    FileSystem sys(associatedFile);
    ASSERT_EQ(sys.getCurrUser()->getName(), "root");

    FILE *associatedFile1;
    associatedFile1 = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    FileSystem sys1(associatedFile1, "arkmagrive");
    ASSERT_EQ(sys1.getCurrUser()->getName(), "arkmagrive");
    ASSERT_NE(sys1.getTableOfUsers().find(std::string("root")), sys.getTableOfUsers().end());
    ASSERT_NE(sys1.getTableOfUsers().find(std::string("arkmagrive")), sys.getTableOfUsers().end());
}

TEST(Setters, AllSetters) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    System::FileSystem sys(associatedFile);
    sys.login("arkmagrive");
    ASSERT_EQ(sys.getCurrUser()->getName(), "arkmagrive");
    std::string root("root");
    ASSERT_NE(sys.getTableOfUsers().find(root), sys.getTableOfUsers().end());
    ASSERT_EQ(sys.getRootDir().getOwner(), 1);
    System::User newUser("tmp_login");
    sys.login(newUser);
    ASSERT_EQ(sys.getCurrUser()->getName(), newUser.getName());
}

TEST(Methods, AdditionalMethods) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    System::FileSystem sys(associatedFile);
    sys.addToTable("login1");
    sys.addToTable("login2");
    ASSERT_EQ(sys.isInTable("login1"), true);
    ASSERT_EQ(sys.isInTable("login2"), true);
    sys.deleteUserFromTable("login2");
    ASSERT_EQ(sys.isInTable("login2"), false);
}

TEST(Exceptions, AllExceptions) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/none", "r");
    EXPECT_ANY_THROW(System::FileSystem sys(associatedFile));
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    System::FileSystem sys(associatedFile);
    EXPECT_ANY_THROW(sys.deleteUserFromTable("root"));
    EXPECT_ANY_THROW(sys.addToTable("root"));
}

TEST(Dirs, DirsMethods) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    FileSystem sys(associatedFile);

    sys.createDir("usr");
    sys.createDir("lib");
    ASSERT_EQ(sys.getRootDir().ls(), "lib usr ");
    sys.setCurrDir("/usr");
    sys.createDir("arkmagrive");
    sys.createDir("ivan");
    sys.setCurrDir("/usr/ivan");
    sys.createFile("INFO_IVAN", 143);
    sys.setCurrDir("/");
    sys.createDir("tmp");
    std::cout << sys.infoSystem();
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}