#include <cstdio>
#include "gtest/gtest.h"
#include "FileSystem.h"
#include "Permissions.h"
#include "User.h"

TEST(Constructor, DefaultConstructor) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");

    System::FileSystem sys(associatedFile);
    ASSERT_NE(sys.getDisk(), nullptr);
    ASSERT_EQ(sys.getCurrUser()->getUserId(), 1);
    ASSERT_EQ(sys.getCurrUser()->getName(), "root");
    ASSERT_EQ(sys.getRootDir().getOwner(), 1);

    System::FileSystem sys2(associatedFile, "arkmagrive");
    ASSERT_NE(sys2.getDisk(), nullptr);
    ASSERT_EQ(sys2.getCurrUser()->getName(), "arkmagrive");
    std::string root("root");
    ASSERT_NE(sys2.getTableOfUsers().find(root), sys2.getTableOfUsers().end());
    ASSERT_EQ(sys2.getRootDir().getOwner(), 1);
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
    sys.deleteFromTable("login2");
    ASSERT_EQ(sys.isInTable("login2"), false);
}

TEST(Exceptions, AllExceptions) {
    FILE *associatedFile;
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/none", "r");
    EXPECT_ANY_THROW(System::FileSystem sys(associatedFile));
    associatedFile = fopen("/Users/stanislavvoronov/oop/lab4/disk", "r");
    System::FileSystem sys(associatedFile);
    EXPECT_ANY_THROW(sys.deleteFromTable("root"));
    EXPECT_ANY_THROW(sys.addToTable("root"));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}