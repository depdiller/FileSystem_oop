//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

class FileSystem {
private:
    Dir& homeDir;
    Dir& rootDir;
    std::vector<User> TableOfUsers;
    User &currUser;
public:
    FileSystem(User&);
    void listUsers();
    void woami();
    bool editTableOfUsrs(currUser&);
    bool eccryptDecrypt(AbstractFile&);
    void statistic();
    void logout();
    void login(std::string userName);
};

#endif //FILESYSTEM_FILESYSTEM_H
