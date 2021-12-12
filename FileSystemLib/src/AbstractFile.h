//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_ABSTRACTFILE_H
#define FILESYSTEM_ABSTRACTFILE_H

#include "Permissions.h"
#include <iostream>
#include <array>

namespace System {
    class AbstractFile {
    protected:
        size_t ownerId;
        size_t size;
        Permissions ouPermissions;
    public:
        AbstractFile(size_t ownerId, unsigned int uoPermissions = 66);
        size_t getOwner() const { return ownerId; }
        void setPermissions(unsigned int codePermissions);
        size_t getSize() { return size; }
        Permissions getPermissions() const { return uoPermissions; }
        virtual void information () const = 0;
    };
}

#endif //FILESYSTEM_ABSTRACTFILE_H
