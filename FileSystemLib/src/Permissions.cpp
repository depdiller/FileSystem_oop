//
// Created by stani on 01.12.2021.
//
#include "Permissions.h"
#include <iostream>

namespace System {
    // rwx constructors
    rwx::rwx(unsigned int codePermission) {
        if (codePermission > 7 || codePermission < 0)
            throw std::invalid_argument("wrong_permission_code");
        read = (codePermission & 0b100) == 4;
        write = (codePermission & 0b010) == 2;
        execute = (codePermission & 0b001) == 1;
    }

    std::string rwx::inText() const {
        char buff[100];
        snprintf(buff, sizeof(buff), "read: %d\twrite: %d\texecute: %d", read, write, execute);
        std::string buffAsStdStr = buff;
        return buff;
    }

    // permissions constructors
    Permissions::Permissions(unsigned int codePermissions) {
        if (codePermissions > 77 || codePermissions < 0)
            throw std::invalid_argument("wrong_permission_code");
        unsigned int uPermissions, oPermissions;
        uPermissions = codePermissions / 10;
        oPermissions = codePermissions % 10;
        this->uoPermissions[0] = rwx(uPermissions);
        this->uoPermissions[1] = rwx(oPermissions);
    }

    Permissions &Permissions::setPermissions(unsigned int codePermissions) {
        if (codePermissions > 77 || codePermissions < 0)
            throw std::invalid_argument("wrong_permission_code");
        unsigned int uPermissions, oPermissions;
        uPermissions = codePermissions / 10;
        oPermissions = codePermissions % 10;
        this->uoPermissions[0] = rwx(uPermissions);
        this->uoPermissions[1] = rwx(oPermissions);
        return *this;
    }

    Permissions &Permissions::operator=(const Permissions &other) {
        if (this != &other) {
            this->uoPermissions = other.uoPermissions;
        }
        return *this;
    }

    std::string Permissions::info() const {
        std::string final;
        char buff1[1024];
        char buff2[1024];
        snprintf(buff1, sizeof(buff1), "User: %s\n", uoPermissions[0].inText().c_str());
        final.append(buff1);
        snprintf(buff2, sizeof(buff2), "Other: %s", uoPermissions[1].inText().c_str());
        final.append(buff2);
        return final;
    }
}