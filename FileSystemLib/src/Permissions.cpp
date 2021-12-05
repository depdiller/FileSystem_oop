//
// Created by stani on 01.12.2021.
//
#include "Permissions.h"
#include <iostream>

namespace System {
//    rwx::rwx(unsigned int codePermission) {
//
//    }

    Permissions::Permissions(unsigned int codePermission) {
        if (codePermission > 7 || codePermission < 0)
            throw std::invalid_argument("wrong_permission_code");
        read = codePermission & 0b100;
        write = codePermission & 0b010;
        execute = codePermission & 0b001;
    }

    Permissions &Permissions::setPermissions(unsigned int codePermission) {
        if (codePermission > 7 || codePermission < 0)
            throw std::invalid_argument("wrong_permission_code");
        this->read = codePermission & 0b100;
        this->write = codePermission & 0b010;
        this->execute = codePermission & 0b001;
        return this;
    }

    unsigned int Permissions::getPermissions() const {
        unsigned int permissions = read + write + execute;
        return permissions;
    }
}
