#include "FileSystem.h"

namespace System {
    FileSystem::FileSystem(FILE *associatedFile, const std::string& username) :  systemStruct() {
        if (associatedFile != nullptr) {
            systemStruct.emplace_back(1, 66);
            disk = associatedFile;
            tableOfUsers.insert(User("root"));
            if (username == "root")
                currUser = tableOfUsers.begin();
            else
                currUser = tableOfUsers.insert(User(username)).first;
        }
        else
            throw std::invalid_argument("cannot associate with this file");
    }

    void FileSystem::deleteUserFromTable(const std::string& username) {
        if (currUser->getUserId() != tableOfUsers.begin()->getUserId())
            throw std::invalid_argument("user have no access for such operation");
        else if (username == "root")
            throw std::invalid_argument("cannot delete root user");
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
        if (currUser->getUserId() != tableOfUsers.begin()->getUserId())
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

    FileSystem &FileSystem::login(const User &newUser) {
        auto it = tableOfUsers.find(newUser.getName());
        if (it == tableOfUsers.end())
            it = tableOfUsers.insert(newUser).first;
        currUser = it;
        return *this;
    }

    FileSystem &FileSystem::login(const std::string& userName) {
        auto it = tableOfUsers.find(userName);
        if (it == tableOfUsers.end()) {
            User newUser(userName);
            it = tableOfUsers.insert(newUser).first;
        }
        currUser = it;
        return *this;
    }

    bool FileSystem::encryptDecrypt(AbstractFile &file) {
        return false;
    }

    bool FileSystem::isInTable(const std::string &username) {
        std::set<User>::iterator it;
        it = tableOfUsers.find(username);
        return it != tableOfUsers.end();
    }
}