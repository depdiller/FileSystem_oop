//
// Created by stani on 30.11.2021.
//

#include "AbstractFile.h"
#include <iostream>

namespace System {
    AbstractFile::AbstractFile(size_t ownerId, unsigned int uoPermissions) : uoPermissions(uoPermissions){
        this->ownerId = ownerId;
        size = 0;
    }

    AbstractFile &AbstractFile::setPermissions(unsigned int codePermissions) {
        if (codePermissions > 77 || codePermissions < 0)
            throw std::invalid_argument("wrong_permission_code");
        uoPermissions = Permissions(codePermissions);
        return *this;
    }

    AbstractFile &AbstractFile::setSize(size_t newSize) {
        this->size = newSize;
        return *this;
    }
}