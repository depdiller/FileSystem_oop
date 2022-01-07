#include "Dir.h"
#include <utility>
#include "File.h"

namespace System {

    Dir::Dir(unsigned int ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions), tableOfDirs(), tableOfFiles() {}

    void Dir::createFile(unsigned int currUserId, unsigned int fileVirtualAdr, const std::string &name) {
        if (tableOfFiles.find(FileId(name, this)) == tableOfFiles.end()) {
            if (checkPermission(currUserId, "w")) {
                File *newFile = new File(fileVirtualAdr, currUserId, 66);
                tableOfFiles.insert(FileId(name, this), newFile);
            }
            else {
                throw std::invalid_argument("No permission");
            }
        }
        else
            throw std::invalid_argument("file with such name already exists");
    }

    void Dir::createDir(unsigned int currUserId, const std::string& name) {
        if (tableOfDirs.find(FileId(name, this)) == tableOfDirs.end()) {
            if (checkPermission(currUserId, "w")) {
                Dir *newDir = new Dir(currUserId);
                tableOfDirs.insert(FileId(name, this), newDir);
            }
            else {
                throw std::invalid_argument("No permission");
            }
        }
        else
            throw std::invalid_argument("dir with such name already exists");
    }

    // скопировать файл filenameThis в папку toDir с новым именем newFilename
    void Dir::copyFile(unsigned int currUserId, Dir &toDir, const std::string& filenameThis,const std::string& newFilename) {
        auto itThisFile = tableOfFiles.find(FileId(filenameThis, this));
        auto itToDirFile = toDir.tableOfFiles.find(FileId(newFilename, &toDir));
        if (itThisFile != tableOfFiles.end() && itToDirFile == toDir.tableOfFiles.end()) {
            if (checkPermission(currUserId, "x") && toDir.checkPermission(currUserId, "x")) {
                // создаем новый пустой файл
                File *newFile = new File();
                // копируем в него данные из старого (будет что-то по типу жесткой ссылки, тк виртуальный адрес = const
                *newFile = *itThisFile->getValue();
                // вставляем файл в папку
                toDir.tableOfFiles.insert(FileId(newFilename, &toDir), newFile);
            }
            else {
                throw std::invalid_argument("No permission to copy file");
            }
        }
        else {
            throw std::invalid_argument("No such file in current dir or in dir copy to have file with such name");
        }
    }

    // копируем текущую папку в toDir под названием dirname
    void Dir::copyDir(unsigned int currUserId, Dir &toDir, const std::string& dirname) {
        // если в toDir уже есть папка с таким именем
        auto it = this->tableOfDirs.find(FileId(dirname, &toDir));
        if (it == toDir.tableOfDirs.end()) {
            if (checkPermission(currUserId, "x") && toDir.checkPermission(currUserId, "x")) {
                // создали новую папку
                Dir *newDir = new Dir(currUserId, 66);
                // скопировали в нее все из текущей
                *newDir = *this;
                // вставили новую папку в toDir
                toDir.tableOfDirs.insert(FileId(dirname, &toDir), newDir);
            } else
                throw std::invalid_argument("No permission to copy dir");
        } else
            throw std::invalid_argument("There is already dir with such name");
    }

    // найти файл в текущей папке и переместить его в toDir
    void Dir::moveFile(unsigned int currUserId, Dir &toDir, const std::string &filenameThis, const std::string &filenameNew) {
        auto itThisFile = tableOfFiles.find(FileId(filenameThis, this));
        auto itToDirFile = toDir.tableOfFiles.find(FileId(filenameNew, &toDir));
        if (itThisFile != tableOfFiles.end() && itToDirFile == toDir.tableOfFiles.end()) {
            if (checkPermission(currUserId, "x") && toDir.checkPermission(currUserId, "x")) {
                // создаем новый пустой файл
                File *newFile = new File();
                // копируем в него данные из старого (будет что-то по типу жесткой ссылки, тк виртуальный адрес = const
                *newFile = *itThisFile->getValue();
                // вставляем файл в папку
                toDir.tableOfFiles.insert(FileId(filenameNew, &toDir), newFile);
                // удаляем файл из текущей дериктории
                tableOfFiles.erase(itThisFile);
            }
            else {
                throw std::invalid_argument("No permission to move file");
            }
        }
        else {
            throw std::invalid_argument("No such file in current dir or in dir copy to have file with such name");
        }
    }

    void Dir::moveDir(unsigned int currUserId, Dir &toDir, const std::string &dirnameThis, const std::string &dirnameNew) {
        auto itThisDir = tableOfDirs.find(FileId(dirnameThis, this));
        auto itToDirDir = toDir.tableOfDirs.find(FileId(dirnameNew, &toDir));
        if (itThisDir != tableOfDirs.end() && itToDirDir == toDir.tableOfDirs.end()) {
            if (checkPermission(currUserId, "x") && toDir.checkPermission(currUserId, "x")) {
                // создали новую папку
                Dir *newDir = new Dir(currUserId, 66);
                // скопировали в нее все из текущей
                *newDir = *itThisDir->getValue();
                // вставили новую папку в toDir
                toDir.tableOfDirs.insert(FileId(dirnameNew, &toDir), newDir);
                // удалить папку из папки, в которой была this
                this->tableOfDirs.erase(itThisDir);
            } else
                throw std::invalid_argument("No permission to move dir");
        } else
            throw std::invalid_argument("No such dir in current dir or in dir copy to have dir with such name");
    }

    Dir &Dir::operator=(const Dir &other) {
        if (this != &other) {
            this->tableOfFiles = other.tableOfFiles;
            this->tableOfDirs = other.tableOfDirs;
            this->uoPermissions = other.uoPermissions;
            this->size = other.size;
            this->ownerId = other.ownerId;
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

    void Dir::deleteFile(unsigned int currUserId, const std::string &filename) {
        auto itThisFile = tableOfFiles.find(FileId(filename, this));
        if (itThisFile != tableOfFiles.end()) {
            if (checkPermission(currUserId, "x")) {
                tableOfFiles.erase(itThisFile);
                // erase data from system
            }
            else {
                throw std::invalid_argument("No permission to delete");
            }
        }
        else {
            throw std::invalid_argument("There is no such file in dir");
        }
    }

    void Dir::deleteDir(unsigned int currUserId, const std::string &dirname) {
        auto itThisDir = tableOfDirs.find(FileId(dirname, this));
        if (itThisDir != tableOfDirs.end()) {
            if (checkPermission(currUserId, "x")) {
                itThisDir->getValue()->recursiveDelete();
                tableOfDirs.erase(itThisDir);
            }
            else {
                throw std::invalid_argument("No permission to delete");
            }
        }
        else {
            throw std::invalid_argument("There is no such file in dir");
        }
    }

    void Dir::recursiveDelete() {
        for (auto it = tableOfFiles.begin(); it != tableOfFiles.end(); ++it) {
            tableOfFiles.erase(it);
        }
        for (auto &dirId : this->tableOfDirs) {
            dirId.getValue()->recursiveDelete();
        }
        for (auto it = tableOfDirs.begin(); it != tableOfDirs.end(); ++it) {
            tableOfDirs.erase(it);
        }
    }

    Dir *Dir::subdir(const std::string &name) {
        auto it = tableOfDirs.find(FileId(name, this));
        if (it != tableOfDirs.end()) {
            return it->getValue();
        }
        else {
            throw std::invalid_argument("No such dir");
        }
    }

    File *Dir::fileIn(const std::string &name) {
        auto it = tableOfFiles.find(FileId(name, this));
        if (it != tableOfFiles.end()) {
            return it->getValue();
        }
        else {
            throw std::invalid_argument("No such file");
        }
    }
}