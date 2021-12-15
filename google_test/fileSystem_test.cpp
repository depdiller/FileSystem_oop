//
// Created by Stanislav Voronov on 15.12.2021.
//
#include "../FileSystemLib/src/FileSystem.h"
#include "../FileSystemLib/src/User.h"
#include "../FileSystemLib/src/EncryptFile.h"
#include "../FileSystemLib/src/File.h"
#include "../FileSystemLib/src/Dir.h"
#include "../FileSystemLib/src/Permissions.h"
#include "../FileSystemLib/src/Descriptor.h"
#include "../FileSystemLib/src/AbstractFile.h"
#include <cstdio>
#include <set>
#include "gtest/gtest.h"

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

// Permissions
TEST(Constructors, DefaultConstructor) {
    System::Permissions pArray = System::Permissions();
    ASSERT_EQ(pArray.getPermissions()[0].isReadable(), true);
    ASSERT_EQ(pArray.getPermissions()[0].isWritable(), true);
    ASSERT_EQ(pArray.getPermissions()[0].isExecutable(), false);
    ASSERT_EQ(pArray.getPermissions()[1].isReadable(), true);
    ASSERT_EQ(pArray.getPermissions()[1].isWritable(), true);
    ASSERT_EQ(pArray.getPermissions()[1].isExecutable(), false);
}

TEST(Setters, DefaultSetters) {
    System::Permissions pArray = System::Permissions();
    pArray.setPermissions(44);
    ASSERT_EQ(pArray.getPermissions()[0].isReadable(), true);
    ASSERT_EQ(pArray.getPermissions()[0].isWritable(), false);
    ASSERT_EQ(pArray.getPermissions()[0].isExecutable(), false);
    ASSERT_EQ(pArray.getPermissions()[1].isReadable(), true);
    ASSERT_EQ(pArray.getPermissions()[1].isWritable(), false);
    ASSERT_EQ(pArray.getPermissions()[1].isExecutable(), false);
}

TEST(PermissionExceptions, AllExceptions) {
    EXPECT_ANY_THROW(System::Permissions pArray = System::Permissions(99));
    EXPECT_ANY_THROW(System::rwx(9));
}

// Descriptor
TEST(DescriptorConstructors, AllConstructors) {
    System::Descriptor d = System::Descriptor("MAIN", 1);
    ASSERT_EQ(d.getStreamName(), "MAIN");
    ASSERT_EQ(d.getVirtualAddress(), 1024);
}

TEST(DescriptorSetters, AllSetters) {
    System::Descriptor d = System::Descriptor("MAIN", 1);
    d.setStreamName("SET");
    ASSERT_EQ(d.getStreamName(), "SET");
}

// File
TEST(FileConstructor, Constructor) {
    System::File f = System::File(1);
    ASSERT_EQ(f.getOwner(), 1);
    ASSERT_EQ(f.getSize(), 0);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isReadable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isWritable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isExecutable(), false);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isReadable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isWritable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isExecutable(), false);
}

TEST(FileSetters, AllSetters) {
    System::File f = System::File(1);
    f.setDateAndTime("22/12/2021");
    ASSERT_EQ(f.getDateAndTime(), "22/12/2021");
    std::set<System::Descriptor> test = f.getStreams();
    std::set<System::Descriptor>::iterator it;
    for( it = test.begin(); it != test.end(); ++it){
        ASSERT_EQ(*it, "MAIN");
    }
    f.setSize(10);
    ASSERT_EQ(f.getSize(), 10);
    f.setPermissions(44);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isReadable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isWritable(), false);
    ASSERT_EQ(f.getPermissions().getPermissions()[0].isExecutable(), false);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isReadable(), true);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isWritable(), false);
    ASSERT_EQ(f.getPermissions().getPermissions()[1].isExecutable(), false);
}

TEST(FileExceptions, AllExceptions) {
    System::File f = System::File(1);
    FILE *imitatePtrFromOpen;
    imitatePtrFromOpen = fopen("C:\\doNotExist", "a+");
    EXPECT_ANY_THROW(f.cat(imitatePtrFromOpen));
    EXPECT_ANY_THROW(f.editFile(imitatePtrFromOpen, "hello"));
    EXPECT_ANY_THROW(f.readFile(imitatePtrFromOpen, 10));
    EXPECT_ANY_THROW(f.writeToFile(imitatePtrFromOpen, "data"));
    EXPECT_ANY_THROW();
}