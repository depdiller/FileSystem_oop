//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DIR_H
#define FILESYSTEM_DIR_H

class Dir : AbstractFile {
private:
    int * virtualAdr;
private:
    Dir();
    void ls(Dir);
    bool mv(Dir dir1, Dir dir2);
    bool rm()
};

#endif //FILESYSTEM_DIR_H
