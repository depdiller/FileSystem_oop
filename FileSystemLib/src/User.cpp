#include "User.h"
#include <iostream>
#include <utility>

namespace System {
    User::User(const std::string& name) : name(name) {
        if (name == "root") {
            userId = 1;
            this->name = name;
        }
        else {
            size_t id = std::hash<std::string>{}(name);
            this->userId = id;
        }
        // the size of the storage space currently allocated for the string
        this->key = name.capacity();
    }

    User::User(const std::string& name, size_t key) : name(name), key(key) {
        if (name == "root")
            userId = 1;
        else {
            size_t id = std::hash<std::string>{}(name);
            this->userId = id;
        }
    }
    User &User::setKey(size_t newKey) {
        key = newKey;
        return *this;
    }
    User &User::setName(std::string newName) {
        name = std::move(newName);
        return *this;
    }

    bool User::operator==(const std::string &username) const {
        return this->getName() == username;
    }
    bool User::operator!=(const std::string &username) const {
        return this->getName() != username;
    }

    bool User::operator<(const User&user) const {
        return this->getUserId() < user.getUserId();
    }

    bool User::operator<(const std::string &username) const {
        return this->getName() < username;
    }

    User &User::operator=(const User &toCopy) {
        if (&toCopy != this) {
            userId = toCopy.userId;
            name = toCopy.name;
            key = toCopy.key;
        }
        return *this;
    }
}