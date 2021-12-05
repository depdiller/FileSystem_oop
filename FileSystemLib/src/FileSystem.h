//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

namespace System {
    class FileSystem {
    private:
        Dir &homeDir;
        Dir &rootDir;
        std::vector <User> TableOfUsers;
        User &currUser;
        static unsigned char umask[2];
    public:
        FileSystem(User &) : umask({'6', '6'}),;

        void listUsers();

        void woami();

        bool editTableOfUsrs(currUser &);

        bool eccryptDecrypt(AbstractFile &);

        void statistic();

        void logout();

        void login(std::string userName);

        bool changeUmask(unsigned int);
    };
}

#endif //FILESYSTEM_FILESYSTEM_H
