#include "gtest/gtest.h"
#include "Permissions.h"


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