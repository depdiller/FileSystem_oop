//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DIR_H
#define FILESYSTEM_DIR_H
#include "AbstractFile.h"

namespace System {
    class Dir : AbstractFile {
    private:
        int *virtualAdr;
    public:
        Dir();
    };
}

#endif //FILESYSTEM_DIR_H
