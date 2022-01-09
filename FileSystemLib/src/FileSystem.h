/**
 * \file
 * \brief Заголовочный файл класса Файловой Системы
 *
 * Данный класс описывает поведение Файловой Системы
 * */
#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <iostream>
#include <cstdio>
#include <list>
#include <set>
#include "User.h"
#include "Dir.h"
#include <string>
#include "AbstractFile.h"
#include <vector>

namespace System {
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Файловая Система
     *
     * Описывает работу Файловой системы на ассоциированным с ней файлом-диском
     *
     * */
    class FileSystem {
    private:
        FILE *disk; ///< ассоциированный файл-диск
        Dir root;
        Dir *currentDir;
        std::set<User> tableOfUsers; ///< таблица пользователей файловой системы
        std::set<User>::iterator currUser; ///< текущий пользователь файловой системы
        unsigned int multForAddresses;
        std::vector<unsigned int> freeSpace;
    public:
        /**
         * \brief стандартный конструктор
         */
        FileSystem(FILE *associatedFile, const std::string &username = "root");

        /**
         * \brief геттер для указателя на диск
         * \throw invalid_argument если ассоциированный файл не существует
         * @return указатель на ассоциированный файл-диск
         */
        FILE *getDisk() const { return disk; }
        FileSystem &setCurrDir(const std::string &path);
        /**
         * \brief геттер для текущего пользователя
         * @return константная ссылка на текущего пользователя
         */
        std::set<User>::iterator getCurrUser() const { return currUser; }

        /**
         * \brief геттер для корневой папки
         * @return константная ссылка на корневую директорию
         */
        const Dir &getRootDir() const { return root; }

        const std::set<User> &getTableOfUsers() const { return tableOfUsers; }

        /**
         * \brief войти в систему в качестве пользователя
         * @param userName имя пользователя
         */
        FileSystem &login(const std::string &userName);

        /**
         * \brief перегрузка метода login
         * (принимает новый объект пользователя)
         */
        FileSystem &login(const User &newUser);

        /**
         * \brief удалить пользователя из таблицы пользователей
         * \throw invalid_argument нет доступа для этой операции
         * \throw invalid_argument нет не такого пользователя в таблице
         * @param username имя пользователя
         */
        void deleteUserFromTable(const std::string &username);

        /**
         * \brief добавить пользователя в таблицу
         * @param username имя пользователя
         * \throw invalid_argument нет доступа для этой операции
         */
        void addToTable(const std::string &username);

        /**
         * \brief зашифровать файл
         * @param file ссылка на файл для шифровки
         * \throw invalid_argument нет прав для такой операции
         * @return успешность операции шифрования
         */
        bool encryptDecrypt(AbstractFile &file);

        /**
         * \brief вывод статистики по файловой системе на экран
         */
        void statistic();

        /**
         * \brief проверка на существование пользователя в таблице пользователей
         * @param username имя пользователя
         * @return есть или нет пользователя в таблице пользователей
         */
        bool isInTable(const std::string &username);
        // methods to control dirs and files

        // изменяет текущую папку, то есь по указателю можно сразу иметь доступ к текущей папке
        Dir *dirByPath(const std::string &dirPath);
        File *fileByPath(const std::string &filePath);
        // создает папку в currentDir
        void createDir(const std::string &dirname);

        void createFile(const std::string &filename, unsigned );

        void deleteDir(const std::string &dirname);

        void deleteFile(const std::string &filename);

        void moveDir(const std::string &dirname, const std::string &path);

        void moveFile(const std::string &filename, const std::string &path);

        void copyDir(const std::string &dirname, const std::string &path);

        void copyFile(const std::string &filename, const std::string &path);

        void writeToFile(const std::string &filePath, const std::string &data);

        std::string readFile(const std::string &filePath, unsigned int charsToRead);

        void editFile(const std::string &filePath, const std::string &dataToAdd);

        std::string catFile(const std::string &filePath);

        std::string infoSystem();
        void recursiveLs(Dir *dir, std::string *buff);

        unsigned int controlVirtualMem();
    };
}
namespace Additional {
    void split(std::string const &str, const char delim, std::vector<std::string> &out);
}

/*TODO:
 * 1. В конструкторе должна быть ссылка на поток,
 * связанная с ассоциированным с файловой системой файлом.
 * Потом через fseek должно отсчитываться смещение по
 * файлу.
 * 2. Проверить нужно ли оставлять extern или можно убрать */
#endif //FILESYSTEM_FILESYSTEM_H
