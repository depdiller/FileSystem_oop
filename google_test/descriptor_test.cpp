#include "gtest/gtest.h"
#include "Descriptor.h"
#include "Permissions.h"

TEST(DescriptorConstructors, AllConstructors) {
    System::Descriptor d_main("MAIN", 1);
    ASSERT_EQ(d_main.getStreamName(), "MAIN");
    ASSERT_EQ(d_main.getVirtualAddress(), 1024);
    System::Descriptor d_crypt("CRYPT", 2);

}

TEST(DescriptorSetters, AllSetters) {
    System::Descriptor d("MAIN", 1);
    d.setStreamName("SET");
    ASSERT_EQ(d.getStreamName(), "SET");
}

TEST(Operators, AllOperators) {
    
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}