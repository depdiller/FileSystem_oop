//
// Created by stani on 01.12.2021.
//

#ifndef FILESYSTEM_PERMISSIONS_H
#define FILESYSTEM_PERMISSIONS_H

namespace System {
    class Permissions {
    private:
        unsigned int read;
        unsigned int write;
        unsigned int execute;
        static unsigned int umask;
    public:
        Permissions(unsigned int permissionList = umask, AbstractFile &);
        bool changeUmask(unsigned int);
        bool setPermissions(unsigned int);
    };
}

#endif //FILESYSTEM_PERMISSIONS_H
