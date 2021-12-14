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

    bool AbstractFile::checkPermission(const std::string& parameter) const {
        bool userCheck = system.getCurrUser().getUserId() == this->ownerId;
        if (parameter != "r" || parameter != "w" || parameter != "x") {
            throw std::invalid_argument("invalid permission check");
        }
        else if (parameter == "r") {
            if (userCheck)
                return uoPermissions.getPermissions()[0].isReadable();
            else
                return uoPermissions.getPermissions()[1].isReadable();
        }
        else if (parameter == "w") {
            if (userCheck)
                return uoPermissions.getPermissions()[0].isWritable();
            else
                return uoPermissions.getPermissions()[1].isWritable();
        }
        else if (parameter == "x") {
            if (userCheck)
                return uoPermissions.getPermissions()[0].isExecutable();
            else
                return uoPermissions.getPermissions()[1].isExecutable();
        }
    }
}