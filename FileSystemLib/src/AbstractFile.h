//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_ABSTRACTFILE_H
#define FILESYSTEM_ABSTRACTFILE_H

#include "Permissions.h"
#include "vector"

namespace System {
    class AbstractFile {
    protected:
        unsigned int owner;
        unsigned char size;
        std::vector<Permissions> permissions;
    public:
        AbstractFile(unsigned int, unsigned char, std::vector<Permissions>);
        virtual usigned getOwner(AbstractFile&) const = 0;
        virtual void setPermissions(AbstractFile&) const = 0 ;
        virtual usined char getSize(AbstractFile&) const = 0;
        virtual void getPermissions(AbstractFile&) const = 0;
        virtual void informations(AbstractFile&) const = 0;
    };
}

#endif //FILESYSTEM_ABSTRACTFILE_H
