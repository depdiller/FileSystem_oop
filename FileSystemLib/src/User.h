//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H

#include <iostream>

namespace System {
    class User {
    private:
        size_t userId;
        std::string name;
        size_t key;
    public:
        User(std::string name);
        User(std::string name, size_t key);
        // getters
        User& setKey(size_t newKey);
        User& setName(std::string newName);
        // setters
        std::string getName() const { return name; };
        size_t getUserId() const { return userId; }
        size_t getKey() const { return key; }
    };
}

#endif //FILESYSTEM_USER_H
