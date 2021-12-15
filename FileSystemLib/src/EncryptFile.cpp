//
// Created by stani on 13.12.2021.
//
#include "EncryptFile.h"

namespace System {
   EncryptFile::EncryptFile(size_t ownerId, unsigned int uoPermissions) : File(ownerId, uoPermissions) {
       tabelOfAccessUsers.insert(ownerId);
   }

    void EncryptFile::addUserToAccess(size_t userId) {
   }
}
