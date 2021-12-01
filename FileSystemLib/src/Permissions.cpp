//
// Created by stani on 01.12.2021.
//
#include "AbstractFile.h"

namespace System {

    Permissions::Permissions(unsigned int permissionList, AbstractFile &) {
    }
    bool Permissions::changeUmask(unsigned int newUmask) {
    }
    bool Permissions::setPermissions(unsigned int) {
    }
}
