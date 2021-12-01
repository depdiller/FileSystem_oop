//
// Created by stani on 30.11.2021.
//

#include "AbstractFile.h"

namespace System {
    AbstractFile::AbstractFile(unsigned int owner, unsigned char size, std::vector<Permissions> permissions) :
    owner(owner),
    size(size) {

    }
}