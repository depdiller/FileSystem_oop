//
// Created by stani on 30.11.2021.
//

#include "AbstractFile.h"
#include <iostream>

namespace System {
    AbstractFile::AbstractFile(size_t ownerId, unsigned int uoPermissions) : ownerId(ownerId), ouPermissions(uoPermissions) {
        size = sizeof(ownerId) + sizeof(permissions);
    }

    void AbstractFile::setPermissions(unsigned int codePermissions) {
        if (codePermissions > 77 || codePermissions < 0)
            throw std::invalid_argument("wrong_permission_code");
        ouPermissions = Permissions(codePermissions);
    }
}