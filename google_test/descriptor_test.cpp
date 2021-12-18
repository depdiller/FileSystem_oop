#include "gtest/gtest.h"
#include "Descriptor.h"
#include "Permissions.h"

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

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}