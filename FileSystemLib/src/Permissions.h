//
// Created by stani on 01.12.2021.
//

#ifndef FILESYSTEM_PERMISSIONS_H
#define FILESYSTEM_PERMISSIONS_H

namespace System {
//    struct rwx {
//    private:
//        unsigned int read;
//        unsigned int write;
//        unsigned int execute;
//    public:
//        explicit rwx(unsigned int codePermission);
//    };
//
    class Permissions {
    private:
        unsigned int read;
        unsigned int write;
        unsigned int execute;
    public:
        explicit Permissions(unsigned int codePermission);
        Permissions& setPermissions(unsigned int codePermission);
        unsigned int getPermissions() const;
    };
}

#endif //FILESYSTEM_PERMISSIONS_H
