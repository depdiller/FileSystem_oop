//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_ENCRYPTFILE_H
#define FILESYSTEM_ENCRYPTFILE_H
#include "File.h"
#include <string>
#include <set>
#include "User.h"

namespace System{
    class EncryptFile : public File {
    private:
        // set of user ids
        std::set<size_t> tabelOfAccessUsers;
    public:
        // constructors
        EncryptFile(size_t ownerId, unsigned int uoPermissions = 66);
        // getters
        std::set<size_t> getTableOfAccess() const { return tabelOfAccessUsers; }
        // setters
        // additional methods
        void addUserToAccess(size_t userId);
    };
}

#endif //FILESYSTEM_ENCRYPTFILE_H
