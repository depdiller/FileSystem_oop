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
}