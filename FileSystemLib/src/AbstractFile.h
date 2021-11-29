//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_ABSTRACTFILE_H
#define FILESYSTEM_ABSTRACTFILE_H

struct FileStruct {
private:
    string fileName;
    char type;
    vector<AbstractFile> structure;
public:
    void pwd();
    FileStruct(string filename, char type);
}

struct Permissions{
private:
    unsigned int read;
    unsigned int write;
    unsigned int execute;
    unsigned int umask;
public:
    Permissions(unsigned int a, AbstractFile&);
    bool changeUmask(unsigned int);
    bool setPermissions(unsigned int);
};

class AbstractFile {
protected:
    User &owner;
    byte size;
    vector<Permissions> permissons;
    FileStruct& structure;
public:
    virtual getOwner(AbstractFile&) = 0;
    virtual getFacl(AbstractFile&);
    virtual getSize(AbstractFile&);
    virtual getType();
};

#endif //FILESYSTEM_ABSTRACTFILE_H
