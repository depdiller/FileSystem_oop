//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_ENCRYPTFILE_H
#define FILESYSTEM_ENCRYPTFILE_H

class EncryptFile : File{
private:
    vector<Users>TableOfAccessUsers;
public:
    checkAccess(User&);
    addToAccess(User&);
};

#endif //FILESYSTEM_ENCRYPTFILE_H
