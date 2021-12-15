//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DIR_H
#define FILESYSTEM_DIR_H
#include "AbstractFile.h"
#include "File.h"
#include <string>
#include <map>

namespace System {
    /*виртуальные адреса папок - с начала файла, то есть потоки
     * начинаются с 1024 байта, а все пространство до этого выделяется
     * под директории и файлы*/
    const size_t bytesForDir = 16;

    class Dir : public AbstractFile {
    private:
        unsigned int virtualAddress;
        /* описатель структуры каталога, в нее входят и подкаталоги
         * еще указатель на родительскую папку, потом указатель на
         * описатель этого файла */
        std::map<std::pair<std::string, Dir*>, AbstractFile*> tableOfFiles;
    public:
        // constructors
        Dir(size_t ownerId, unsigned int uoPermissions = 66);
        // additional methods
        void showContentDir();
            // fileOrDir = 'f' / 'd'
        void create(char fileOrDir, const std::string& name);
        void copy();
        void move();
        void deleteFile();
        void changeName();

        void information() const override;
    };
}

#endif //FILESYSTEM_DIR_H
