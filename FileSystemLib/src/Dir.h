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
//    template<typename T, typename V>
//    class pair {
//    private:
//        T first;
//        V *second;
//    public:
//        pair();
//        pair(T first, V second);
//        bool operator==(const pair<T, V> &other);
//        bool operator!=(const pair<T, V> &other);
//        bool operator<(const pair<T, V> &other);
//    };
//    template<typename T, typename V>
//    bool pair<T, V>::operator==(const pair<T, V> &other) {
//        return first == other.first;
//    }
//    template<typename T, typename V>
//    bool pair<T, V>::operator!=(const pair<T, V> &other) {
//        return first != other.first;
//    }
//    template<typename T, typename V>
//    bool pair<T, V>::operator<(const pair<T, V> &other) {
//        return this->first < other.first;
//    }
//
//    template<typename T, typename V>
//    pair<T, V>::pair(T first, V second) {
//        this->first = first;
//        this->second = second;
//    }
//
//    template<typename T, typename V>
//    pair<T, V>::pair() = default;;

    class Dir : public AbstractFile {
    private:
        /* описатель структуры каталога, в нее входят и подкаталоги
         * еще указатель на родительскую папку, потом указатель на
         * описатель этого файла */

        /**
         * таблица ассоциированных с директорией файлов
         * могут быть как файлы, так и поддиректории
         */

//        TemplateMap::Map<std::string, Dir*> tableOfDirs;
        TemplateMap::Map<std::string, File*> tableOfFiles;
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
        /**
         * \brief скопировать файл или подкаталог
         */
        void copyFile(unsigned int currUserId, Dir &copyTo, const std::string& filename);
        void copyDir(unsigned int currUserId, Dir &copyTo, const std::string& dirname);
        /**
         * \brief переместить файл или подкаталог
         */
        void moveFile(unsigned int currUserId, Dir &toDir, const std::string& filename);
        void moveDir(unsigned int currUserId, Dir &toDir, const std::string& dirname);
        /**
         * \brief удалить файл или подкатолог
         */
        void deleteFile();
        /**
         * \brief перегрузка родительского метода, выводит информацию о папке
         */
        void information() const override;
        /**
         * \brief вывести содержимое папки
         */
        void showContentDir();
    };
}

#endif //FILESYSTEM_DIR_H
