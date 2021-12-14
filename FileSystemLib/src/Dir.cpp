//
// Created by stani on 12.12.2021.
//
#include "Dir.h"
#include "FileSystem.h"

namespace System {

    Dir::Dir(size_t ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions) {
        virtualAddress = bytesForDir;
    }

    void Dir::create(char fileOrDir, std::string name) {
        if (fileOrDir == 'f') {
            Dir newDir = Dir(currSystem->getCurrUser().getUserId(), 66);
            tableOfFiles.insert(std::make_pair(std::make_pair(name, *this), newDir));
        }
        else if (fileOrDir == 'd') {

        }
        else
            throw std::invalid_argument("creating unknown type");
    }

    void Dir::information() const {
    }
}
