//
// Created by stani on 30.11.2021.
//
#include "FileSystem.h"

namespace System {
    FileSystem::FileSystem(FILE *associatedFile, const std::string& username) : currUser(username), rootDir(){
        disk = associatedFile;
        tableOfUsers.insert(User(std::string("root")));
        currUser = *tableOfUsers.begin();
    }

    // return to root-user or just exit the program
    int FileSystem::exit() {
        if (currUser.getUserId() == 1)
            return 0;
        else {
            setCurrUser(*tableOfUsers.begin());
            return 1;
        }
    }

    void FileSystem::listUsers() {
        for (const User& u : tableOfUsers)
            std::cout << u.getName() << std::endl;
    }

    void FileSystem::whoami() {
        std::cout << currUser.getName();
    }

    // creating new user or logging as an existing one
    void FileSystem::login(const std::string& userName) {
        for (const User& u : tableOfUsers) {
            if (u == userName) {
                currUser = u;
                return;
            }
        }
        User newUser = User(userName);
        currUser = newUser;
    }

    void FileSystem::deleteFromTable(const std::string& username) {
        if (currUser.getUserId() != tableOfUsers.begin()->getUserId())
            throw std::invalid_argument("user have no access for such operation");
        std::set<User>::iterator it;
        it = tableOfUsers.find(username);
        if (it != tableOfUsers.end()) {
            tableOfUsers.erase(it);
        }
        else {
            throw std::invalid_argument("no such user");
        }
    }

    void FileSystem::addToTable(const std::string &username) {
        if (currUser.getUserId() != tableOfUsers.begin()->getUserId())
            throw std::invalid_argument("user have no access for such operation");
        std::set<User>::iterator it;
        it = tableOfUsers.find(username);
        if (it == tableOfUsers.end()) {
            tableOfUsers.insert(User(std::string(username)));
        }
        else {
            throw std::invalid_argument("already have such user");
        }
    }

    void FileSystem::setCurrUser(const User &newUser) {
        currUser = newUser;
    }

    bool FileSystem::eccryptDecrypt(AbstractFile &) {
        return false;
    }
}