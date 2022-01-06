#include "Dir.h"
#include <utility>
#include "File.h"

namespace System {

    Dir::Dir(unsigned int ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions), tableOfDirs(), tableOfFiles() {}

    void Dir::createFile(unsigned int currUserId, unsigned int fileVirtualAdr, const std::string &name) {
        if (tableOfFiles.find(FileId(name, this)) == tableOfFiles.end()) {
            File *newFile = new File(fileVirtualAdr, currUserId, 66);
            tableOfFiles.insert(FileId(name, this), newFile);
        }
        else
            throw std::invalid_argument("file with such name already exists");
    }

    void Dir::createDir(unsigned int currUserId, const std::string& name) {
        if (tableOfDirs.find(FileId(name, this)) == tableOfDirs.end()) {
            Dir *newDir = new Dir(currUserId);
            tableOfDirs.insert(FileId(name, this), newDir);
        }
        else
            throw std::invalid_argument("dir with such name already exists");
    }

    void Dir::copyFile(unsigned int currUserId, Dir &toDir, const std::string& filename) {
        auto it = this->tableOfFiles.find(FileId(filename, this));
        if (it != tableOfFiles.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfFiles.insert(FileId(filename, this), it->getValue());
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("File not found");
    }

    void Dir::copyDir(unsigned int currUserId, Dir &toDir, const std::string& dirname) {
        auto it = this->tableOfDirs.find(FileId(dirname, this));
        if (it != tableOfDirs.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfDirs.insert(FileId(dirname, this), it->getValue());
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("Dir not found");
    }

    void Dir::moveFile(unsigned int currUserId, Dir &toDir, const std::string &filename) {
        auto it = this->tableOfFiles.find(FileId(filename, this));
        if (it != tableOfFiles.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfFiles.insert(FileId(filename, this), it->getValue());
                tableOfFiles.erase(it);
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("File not found");
    }

    void Dir::moveDir(unsigned int currUserId, Dir &toDir, const std::string &dirname) {
        auto it = this->tableOfDirs.find(FileId(dirname, this));
        if (it != tableOfDirs.end()) {
            if (checkPermission(currUserId, "x")) {
                toDir.tableOfDirs.insert(FileId(dirname, this), it->getValue());
                tableOfDirs.erase(it);
            }
            else
                throw std::invalid_argument("do not have permission for such operation");
        }
        else
            throw std::invalid_argument("Dir not found");
    }

    Dir &Dir::operator=(const Dir &other) {
        if (this != &other) {
            this->tableOfFiles = other.tableOfFiles;
            this->tableOfDirs = other.tableOfDirs;
            this->uoPermissions = other.uoPermissions;
        }
        return *this;
    }

    std::string Dir::information() const {
        char buff[100];
        char dirs[100];
        char files[100];
        std::string final;
        if (tableOfDirs.size() != 0) {
            final.append("Dirs in directory: ");
            for (auto const &dir: tableOfDirs) {
                snprintf(dirs, sizeof(dirs), "%s ", dir.getKey().first.c_str());
                final.append(dirs);
            }
            final.append("\t");
        }
        if (tableOfFiles.size() != 0) {
            final.append("Files in directory: ");
            for (auto const &file: tableOfFiles) {
                snprintf(files, sizeof(files), "%s ", file.getKey().first.c_str());
                final.append(files);
            }
            final.append("\t");
        }
        snprintf(buff, sizeof(buff), "OwnerId: %d, size: %zu", ownerId, size);
        final.append(buff);
        return final;
    }
    Dir &Dir::operator=(Dir &&other)  noexcept {
        if (this != &other) {
            this->tableOfFiles = other.tableOfFiles;
            this->tableOfDirs = other.tableOfDirs;
            this->uoPermissions = other.uoPermissions;
        }
        return *this;
    }
}
