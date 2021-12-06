//
// Created by stani on 05.12.2021.
//
#include "User.h"
#include <iostream>
#include <utility>

namespace System {
    User::User(std::string name) : name(name){
        size_t id = std::hash<std::string>{} (name);
        this->userId = id;
        // the size of the storage space currently allocated for the string
        this->key = name.capacity();
    }
    User::User(std::string name, size_t key) : name(name), key(key) {
        size_t id = std::hash<std::string>{} (name);
        this->userId = id;
    }
    User &User::setKey(size_t newKey) {
        key = newKey;
        return *this;
    }

    User &User::setName(std::string newName) {
        name = std::move(newName);
        return *this;
    }
}