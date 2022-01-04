#include "gtest/gtest.h"
#include "User.h"
#include <utility>

TEST(Constructors, AllConstructors) {
    System::User user1("user1");
    ASSERT_EQ(user1.getName(), "user1");
    ASSERT_EQ(user1.getUserId(), std::hash<std::string>{}("user1"));
    ASSERT_EQ(user1.getKey(), std::string("user1").capacity());

    System::User user2("user2", 14324312312);
    ASSERT_EQ(user2.getKey(), 14324312312);
}

TEST(Setters, AllSetters) {
    System::User user1 = System::User("user1");
    user1.setKey(123).setName("anotherUser");
    ASSERT_EQ( user1.getKey(), 123);
    ASSERT_EQ(user1.getName(), "anotherUser");
}

TEST(Operators, AllOperators) {
    System::User user1("user1");
    System::User user2("user2");
    ASSERT_EQ(true, user1 < user2);
    ASSERT_EQ(true, user1 < "user2");
    ASSERT_EQ(false, user1 == "user2");
    ASSERT_EQ(true, user1 != "user2");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
