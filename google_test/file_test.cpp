#include <cstdio>
#include <set>
#include "gtest/gtest.h"
#include "File.h"
#include "Descriptor.h"
#include "Permissions.h"

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
}