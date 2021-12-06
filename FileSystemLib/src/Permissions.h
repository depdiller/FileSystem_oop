//
// Created by stani on 01.12.2021.
//

#ifndef FILESYSTEM_PERMISSIONS_H
#define FILESYSTEM_PERMISSIONS_H
#include <array>

namespace System {
    struct rwx {
    private:
        bool read;
        bool write;
        bool execute;
    public:
        explicit rwx(unsigned int codePermission = 66);

        // move constructor
    };

    class Permissions {
    private:
        std::array<rwx, 2> uoPermissions;
    public:
        explicit Permissions(unsigned int codePermissions);
        Permissions& setPermissions(unsigned int codePermission);
        std::array<rwx, 2> getPermissions() const { return uoPermissions; }
    };
}

#endif //FILESYSTEM_PERMISSIONS_H
