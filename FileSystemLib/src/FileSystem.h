//
// Created by stani on 13.12.2021.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include "User.h"
#include "Dir.h"
#include "string"
#include "AbstractFile.h"

namespace System {
    class FileSystem {
    private:
        FILE *disk;
        Dir rootDir;
        std::set<User> tableOfUsers;
        User currUser;
    public:
        // constructors
        FileSystem(FILE *associatedFile, const std::string& username = "root");
        // getters
        FILE *getDisk() const { return disk; }
        User &getCurrUser() const { return currUser; }
        // custom setters
        void login(const std::string& userName);
        void setCurrUser(const User&);
        // additional functions
        void listUsers();
        void whoami();
        void deleteFromTable(const std::string& username);
        void addToTable(const std::string& username);
        bool eccryptDecrypt(AbstractFile&);
        void statistic();
        int exit();
    };

    extern FileSystem *currSystem;
}

/*TODO:
 * 1. В конструкторе должна быть ссылка на поток,
 * связанная с ассоциированным с файловой системой файлом.
 * Потом через fseek должно отсчитываться смещение по
 * файлу.
 * 2. Проверить нужно ли оставлять extern или можно убрать*/
#endif //FILESYSTEM_FILESYSTEM_H
}

#endif //FILESYSTEM_FILESYSTEM_H
