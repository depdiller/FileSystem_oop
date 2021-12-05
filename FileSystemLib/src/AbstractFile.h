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
        std::array<int, 2> permissions;
    public:
        AbstractFile(size_t ownerId, std::array<int, 2> = {6, 6});
        virtual usigned getOwner(AbstractFile&) const = 0;
        virtual void setPermissions(AbstractFile&) const = 0 ;
        virtual usined char getSize(AbstractFile&) const = 0;
        virtual void getPermissions(AbstractFile&) const = 0;
        virtual void informations(AbstractFile&) const = 0;
    };
}

#endif //FILESYSTEM_ABSTRACTFILE_H
