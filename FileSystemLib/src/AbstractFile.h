//
// Created by stani on 24.11.2021.
//
#ifndef FILESYSTEM_ABSTRACTFILE_H
#define FILESYSTEM_ABSTRACTFILE_H

#include "Permissions.h"
#include <iostream>

namespace System {
    class AbstractFile {
    protected:
        size_t ownerId;
        size_t size;
        Permissions uoPermissions;
    public:
        // constructors
        explicit AbstractFile(size_t ownerId, unsigned int uoPermissions = 66);
        // setters
        AbstractFile& setPermissions(unsigned int codePermissions);
        AbstractFile& setSize(size_t newSize);
        // getters
        size_t getOwner() const { return ownerId; }
        size_t getSize() { return size; }
        Permissions getPermissions() const { return uoPermissions; }
        // additional
        virtual void information () const = 0;
        void edit();
        // "r" "w" "x"
        bool checkPermission(size_t currUserId, const std::string& parameter) const;
    };
}
/*TODO
 * 1. Добавить виртуальный деструктор
 * 2. Добавть
 * */

#endif //FILESYSTEM_ABSTRACTFILE_H
