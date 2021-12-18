//
// Created by stani on 12.12.2021.
//
#include "Dir.h"
#include "FileSystem.h"

namespace System {

    Dir::Dir(size_t ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions) {
        virtualAddress = bytesForDir;
    }

    void Dir::create(size_t currUserId, char fileOrDir, const std::string& name) {
        if (fileOrDir == 'f') {
            File newFile = File(currUserId);
            File *ptrFileDescriptor = &newFile;
            tableOfFiles.insert(std::make_pair(std::make_pair(name, this), ptrFileDescriptor));
        }
        else if (fileOrDir == 'd') {
            Dir newDir = Dir(currUserId);
            AbstractFile *ptrDirDescriptor = &newDir;
            tableOfFiles.insert(std::make_pair(std::make_pair(name, this), ptrDirDescriptor));
        }
        else
            throw std::invalid_argument("creating unknown type");
    }

    void Dir::information() const {
    }
}
