/**
 * \file
 * \brief Заголовочный файл класса Директории
 *
 * Данный класс является дочерним по отношению к
 * классу Абстрактный файл. Описывает структуру директории
 * в файловой системе
 * */
#ifndef FILESYSTEM_DIR_H
#define FILESYSTEM_DIR_H
#include "AbstractFile.h"
#include "File.h"
#include <string>
#include "Map.h"
#include <map>
#include <utility>

namespace System {
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Директории
     *
     * Класс для описания характеристик папок, лежащих на диске
     * */
    class Dir;
    class FileId : public std::pair<std::string, Dir*> {
    public:
        FileId() {
            first = std::string();
            second = nullptr;
        }
        FileId(std::string name, Dir *parent) {
            first = std::move(name);
            second = parent;
        }
        bool operator<(const std::string &other) {
            return this->first < other;
        }
    };

    class Dir : public AbstractFile {
    private:
        /* описатель структуры каталога, в нее входят и подкаталоги
         * еще указатель на родительскую папку, потом указатель на
         * описатель этого файла */

        /**
         * таблица ассоциированных с директорией файлов
         * могут быть как файлы, так и поддиректории
         */

        TemplateMap::Map<FileId, Dir*> tableOfDirs;
        TemplateMap::Map<FileId, File*> tableOfFiles;
    public:
        /**
         * \brief стандартный конструктор
         *
         * @param ownerId идентификатор владельца папки
         * @param uoPermissions набор разрешений для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
         */
        Dir(unsigned int ownerId, unsigned int uoPermissions = 66);
        ~Dir() override = default;;
        Dir &operator=(const Dir &other);
//        Dir &operator=(Dir &&other);

        int getNumberOfSubdir() const { return tableOfDirs.size(); }
        int getNumberOfFiles() const { return tableOfFiles.size(); }
        const TemplateMap::Map<FileId, Dir*> &getTableOfDirs() const { return tableOfDirs; }
        const TemplateMap::Map<FileId, File*> &getTableOfFiles() const { return tableOfFiles; }
        /**
         * \brief создать поддиректорию или файл в текущей папке
         *
         * @param currUserId идентификатор текущего пользователя файловой системы
         * @param fileOrDir создать подкаталог или файл
         * @param name имя нового объекта
         * \throw invalid_argument при некорректном типе создаваемого объекта
         */
        void createFile(unsigned int currUserId, unsigned int fileVirtualAdr, const std::string& name);
        void createDir(unsigned int currUserId, const std::string& name);
//        void createDir(const Dir &dir);
        /**
         * \brief скопировать файл или подкаталог
         */
        void copyFile(unsigned int currUserId, Dir &copyTo, const std::string& filename, const std::string& newFilename);
        void copyDir(unsigned int currUserId, Dir &copyTo, const std::string& dirname);
        /**
         * \brief переместить файл или подкаталог
         */
        void moveFile(unsigned int currUserId, Dir &toDir, const std::string &filenameThis, const std::string& filename);
        void moveDir(unsigned int currUserId, Dir &toDir, const std::string& dirnameThis, const std::string &dirnameNew);
        /**
         * \brief удалить файл или подкатолог
         */
        void deleteFile(unsigned int currUserId, const std::string &filename);
        void deleteDir(unsigned int currUserId, const std::string &dirname);
        /**
         * \brief перегрузка родительского метода, выводит информацию о папке
         */
        std::string information() const override;
        /**
         * \brief вывести содержимое папки
         */
         void recursiveDelete();
         Dir *subdir(const std::string &name);
         File *fileIn(const std::string &name);
    };
}

#endif //FILESYSTEM_DIR_H
