#include "Dir.h"
#include <utility>
#include "File.h"

namespace System {

    Dir::Dir(unsigned int ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions) {
        tableOfFiles = TemplateMap::Map<std::string, File*>();
    }

    void Dir::createFile(unsigned int currUserId, unsigned int fileVirtualAdr, const std::string &name) {
        if (tableOfFiles.find(name) == tableOfFiles.end()) {
            File *newFile = new File(fileVirtualAdr, currUserId, 66);
            tableOfFiles.insert(name, newFile);
        }
        else
            throw std::invalid_argument("file with such name already exists");
    }

//    void Dir::createDir(size_t currUserId, const std::string& name) {
//        if (tableOfDirs.find(name) == tableOfDirs.end()) {
//            Dir *newDir = new Dir(currUserId);
//            tableOfDirs.insert(name, newDir);
//        }
//        else
//            throw std::invalid_argument("dir with such name already exists");
//    }

    void Dir::copyFile(unsigned int currUserId, Dir &toDir, const std::string& filename) {
        auto it = this->tableOfFiles.find(filename);
        if (it != tableOfFiles.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfFiles.insert(filename, it->getValue());
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("File not found");
    }

//    void Dir::copyDir(size_t currUserId, Dir &toDir, const std::string& dirname) {
//        auto it = this->tableOfDirs.find(dirname);
//        if (it != tableOfDirs.end()) {
//            if (checkPermission(currUserId, "x")) {
//                toDir.tableOfDirs.insert(dirname, it->getValue());
//            }
//            else
//                throw std::invalid_argument("do not have permission for such operation");
//        }
//        else
//            throw std::invalid_argument("Dir not found");
//    }

    void Dir::moveFile(unsigned int currUserId, Dir &toDir, const std::string &filename) {
        auto it = this->tableOfFiles.find(filename);
        if (it != tableOfFiles.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfFiles.insert(filename, it->getValue());
                tableOfFiles.erase(it);
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("File not found");
    }

//    void Dir::moveDir(size_t currUserId, Dir &toDir, const std::string &dirname) {
//        auto it = this->tableOfDirs.find(dirname);
//        if (it != tableOfDirs.end()) {
//            if (checkPermission(currUserId, "x")) {
//                toDir.tableOfDirs.insert(dirname, it->getValue());
//                tableOfDirs.erase(it);
//            }
//            else
//                throw std::invalid_argument("do not have permission for such operation");
//        }
//        else
//            throw std::invalid_argument("Dir not found");
//    }

    Dir &Dir::operator=(const Dir &other) {
        if (this != &other) {
            tableOfFiles = other.tableOfFiles;
//            tableOfDirs = other.tableOfDirs;
        }
        return *this;
    }

    void Dir::information() const {
    }
}
