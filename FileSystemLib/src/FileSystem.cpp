#include "FileSystem.h"

namespace System {
    FileSystem::FileSystem(FILE *associatedFile, const std::string& username) : currentDir(nullptr),
    root(1, 66), freeSpace(), pwd() {
        if (associatedFile != nullptr) {
            currentDir = &root;
            disk = associatedFile;
            tableOfUsers.insert(User("root"));
            if (username == "root")
                currUser = tableOfUsers.begin();
            else
                currUser = tableOfUsers.insert(User(username)).first;
            multForAddresses = 0;
            pwd = "/";
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

    Dir *FileSystem::dirByPath(const std::string &dirPath) {
        if (dirPath[0] != '/') {
            throw std::invalid_argument("Incorrect path");
        }
        Dir *ptr_toDir = &root;
        std::vector<std::string> path;
        Additional::split(dirPath, '/', path);
        for (const std::string &dirname: path) {
            auto it = ptr_toDir->getTableOfDirs().find(FileId(dirname, ptr_toDir));
            if (it == ptr_toDir->getTableOfDirs().end()) {
                throw std::invalid_argument("No such dir");
            }
            ptr_toDir = it->getValue();
        }
        return ptr_toDir;
    }

    void FileSystem::createDir(const std::string &dirname) {
        try {
            currentDir->createDir(currUser->getUserId(), dirname);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::createFile(const std::string &filename, unsigned int vAddress) {
        try {
            currentDir->createFile(currUser->getUserId(), vAddress, filename);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::deleteDir(const std::string &dirname) {
        try {
            currentDir->deleteDir(currUser->getUserId(), dirname);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::deleteFile(const std::string &filename) {
        try {
            currentDir->deleteFile(currUser->getUserId(), filename);

            auto it = currentDir->getTableOfFiles().find(FileId(filename, currentDir));
            if (it != currentDir->getTableOfFiles().end()) {
                freeSpace.push_back(it->getValue()->getStreams().find(std::string("MAIN"))->getVirtualAddress());
            }
            // else не нужен, тк если бы файла не было, исключение бы выкинулось до
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }
    // можно добавить второе имя, которое будет новым именем папки, но пока так
    // из текущей директории по имени -> в папку по пути
    void FileSystem::moveDir(const std::string &dirname, const std::string &path) {
        try {
            Dir &toDir = *dirByPath(path);
            currentDir->moveDir(currUser->getUserId(), toDir, dirname, dirname);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::moveFile(const std::string &filename, const std::string &path) {
        try {
            Dir &toDir = *dirByPath(path);
            currentDir->moveFile(currUser->getUserId(), toDir, filename, filename);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::copyDir(const std::string &dirname, const std::string &path) {
        try {
            Dir &toDir = *dirByPath(path);
            currentDir->copyDir(currUser->getUserId(), toDir, dirname, dirname);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::copyFile(const std::string &filename, const std::string &path) {
        try {
            Dir &toDir = *dirByPath(path);
            currentDir->copyFile(currUser->getUserId(), toDir, filename, filename);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    FileSystem &FileSystem::setCurrDir(const std::string &path) {
        try {
            currentDir = dirByPath(path);
            pwd = path;
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
        return *this;
    }

    std::string FileSystem::infoSystem() {
        std::string info;
        info.append("root: ");
        recursiveLs(&root, &info);
        return info;
    }

    void FileSystem::recursiveLs(Dir *dir, std::string *buff) {
        // записываем в строку данные из текущей папки
        for (auto &dirToPrint : dir->getTableOfDirs()) {
            buff->append(dirToPrint.getKey().first + ' ');
        }
        for (auto &fileToPrint : dir->getTableOfFiles()) {
            buff->append(fileToPrint.getKey().first + ' ');
        }
        buff->append("\n");

        // рекурсия для всех папок внутри
        for (auto &dirId : dir->getTableOfDirs()) {
            buff->append(dirId.getKey().first + ": ");
            recursiveLs(dirId.getValue(), buff);
        }
    }

    unsigned int FileSystem::controlVirtualMem() {
        unsigned int address;
        if (!freeSpace.empty()) {
            address = freeSpace.back();
            freeSpace.pop_back();
        }
        else {
            address = stdSize * multForAddresses;
        }
        return address;
    }

    void FileSystem::writeToFile(const std::string &filePath, const std::string &data) {
        try {
            File &file = *fileByPath(filePath);
            FILE *stream = file.open(disk, currUser->getUserId(), "w");
            file.writeToFile(stream, data);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    std::string FileSystem::catFile(const std::string &filePath) {
        try {
            File &file = *fileByPath(filePath);
            FILE *stream = file.open(disk, currUser->getUserId(), "r");
            return file.cat(stream);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    std::string FileSystem::readFile(const std::string &filePath, unsigned int charsToRead) {
        try {
            File &file = *fileByPath(filePath);
            FILE *stream = file.open(disk, currUser->getUserId(), "r");
            return file.readFile(stream, charsToRead);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::editFile(const std::string &filePath, const std::string &dataToAdd) {
        try {
            File &file = *fileByPath(filePath);
            FILE *stream = file.open(disk, currUser->getUserId(), "w");
            return file.editFile(stream, dataToAdd);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    File *FileSystem::fileByPath(const std::string &filePath) {
        if (filePath[0] != '/') {
            throw std::invalid_argument("Incorrect path");
        }
        Dir *ptr_toDir = &root;
        std::vector<std::string> path;
        Additional::split(filePath, '/', path);
        std::string filename = path.back();
        path.pop_back();
        for (const std::string &dirname: path) {
            auto it = ptr_toDir->getTableOfDirs().find(FileId(dirname, ptr_toDir));
            if (it == ptr_toDir->getTableOfDirs().end()) {
                throw std::invalid_argument("No such dir");
            }
            ptr_toDir = it->getValue();
        }
        auto it_toFile = ptr_toDir->getTableOfFiles().find(FileId(filename, ptr_toDir));
        if (it_toFile == ptr_toDir->getTableOfFiles().end()) {
            throw std::invalid_argument("No such file");
        }
        return it_toFile->getValue();
    }

    void FileSystem::changePermissionsDir(const std::string &dirPath, unsigned int newPermissions) {
        try {
            Dir &toDir = *dirByPath(dirPath);
            toDir.setPermissions(newPermissions);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }

    void FileSystem::changePermissionsFile(const std::string &filePath, unsigned int newPermissions) {
        try {
            File &file = *fileByPath(filePath);
            file.setPermissions(newPermissions);
        }
        catch (std::invalid_argument &msg) {
            throw;
        }
    }
}

namespace Additional {
    void split(std::string const &str, const char delim, std::vector<std::string> &out) {
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }
}