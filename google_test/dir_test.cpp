#include "Dir.h"
#include "gtest/gtest.h"
#include "FileSystem.h"

TEST(Constructors, ConstructorsTest) {
    System::Dir dir(1, 66);
    ASSERT_EQ(dir.getOwner(), 1);
    ASSERT_EQ(dir.getSize(), 0);
    ASSERT_EQ(dir.checkPermission(1, "r"), true);
    ASSERT_EQ(dir.checkPermission(1, "w"), true);
    ASSERT_EQ(dir.checkPermission(1, "x"), false);
    ASSERT_EQ(dir.getNumberOfFiles(), 0);
    ASSERT_EQ(dir.getNumberOfSubdir(), 0);
}

TEST(Subdirs, NestedDirs) {
    System::Dir dir(1, 66);
    dir.createDir(1, "dir1");
    ASSERT_EQ(dir.getNumberOfSubdir(), 1);
    ASSERT_NE(dir.getTableOfDirs().find(System::FileId("dir1", &dir)), dir.getTableOfDirs().end());
    ASSERT_EQ(dir.getTableOfDirs().find(System::FileId("dir2", &dir)), dir.getTableOfDirs().end());
    dir.createDir(1, "dir2");
    EXPECT_ANY_THROW(dir.createDir(1, "dir2"));
    ASSERT_EQ(dir.getNumberOfSubdir(), 2);
    ASSERT_NE(dir.getTableOfDirs().find(System::FileId("dir1", &dir)), dir.getTableOfDirs().end());
    ASSERT_NE(dir.getTableOfDirs().find(System::FileId("dir2", &dir)), dir.getTableOfDirs().end());

    dir.createFile(1, 221, "file1");
    dir.createFile(1, 231, "file2");
    ASSERT_EQ(dir.getNumberOfFiles(), 2);
    ASSERT_NE(dir.getTableOfFiles().find(System::FileId("file1", &dir)), dir.getTableOfFiles().end());
    ASSERT_NE(dir.getTableOfFiles().find(System::FileId("file2", &dir)), dir.getTableOfFiles().end());

    EXPECT_ANY_THROW(dir.createDir(1, "dir1"));
    EXPECT_ANY_THROW(dir.createFile(1, 346, "file1"));

    ASSERT_EQ(dir.information(), "Dirs in directory: dir1 dir2 \tFiles in directory: file1 file2 \t"
                                 "OwnerId: 1, size: 0");
}

using namespace  System;
TEST(MoveAndCopy, CopyMoveMethods) {
    Dir dir(1, 44);
    EXPECT_ANY_THROW(dir.createDir(1, "usr"));
    dir.setPermissions(66);
    dir.createDir(1, "usr");
    dir.createDir(1, "lib");
    ASSERT_EQ(dir.information(), "Dirs in directory: lib usr \tOwnerId: 1, size: 0");
    auto usr = dir.getTableOfDirs().find(FileId("usr", &dir))->getValue();
    usr->createDir(1, "arkmagrive");
    ASSERT_EQ(usr->information(), "Dirs in directory: arkmagrive \tOwnerId: 1, size: 0");
    ASSERT_EQ(dir.information(), "Dirs in directory: lib usr \tOwnerId: 1, size: 0");
    auto arkmagrive = usr->getTableOfDirs().find(FileId("arkmagrive", usr))->getValue();
    arkmagrive->createFile(1, 223, "arkmagrive_info");
    ASSERT_EQ(arkmagrive->information(), "Files in directory: arkmagrive_info \tOwnerId: 1, size: 0");

    EXPECT_ANY_THROW(usr->moveDir(1, dir, "arkmagrive", "arkmagrive_moved"));
    arkmagrive->setPermissions(77);
    dir.setPermissions(77);
    usr->setPermissions(77);
    usr->moveDir(1, dir, "arkmagrive", "arkmagrive_moved");
    ASSERT_EQ(dir.information(), "Dirs in directory: arkmagrive_moved lib usr \tOwnerId: 1, size: 0");
    ASSERT_EQ(usr->information(), "OwnerId: 1, size: 0");
    auto arkmagrive_moved = dir.getTableOfDirs().find(FileId("arkmgarive_moved", &dir))->getValue();
    ASSERT_EQ(arkmagrive_moved->information(), "Files in directory: arkmagrive_info \tOwnerId: 1, size 0");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}