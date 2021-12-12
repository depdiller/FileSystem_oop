//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H
#include "Dir.h"
#include <iostream>

namespace System {
    class User {
    private:
        size_t userId;
        std::string name;
        size_t key;
        Dir &homeDir;
    public:
        // constructors
        User(const std::string& name);
        User(const std::string& name, size_t key);
        // setters
        User& setKey(size_t newKey);
        User& setName(std::string newName);
        // getters
        std::string getName() const { return name; }
        size_t getUserId() const { return userId; }
        size_t getKey() const { return key; }
        // operators
        bool operator==(const std::string &username) const;
        bool operator!=(const std::string &username) const;
        bool operator<(const User&) const;
        bool operator<(const std::string &username) const;
        User &operator=(const User&);
    };
}

/*TODO
 * 1. копирующий оператор проверить в файловой системе в login */

#endif //FILESYSTEM_USER_H
