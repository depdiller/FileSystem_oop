/**
 * \file
 * \brief Заголовочный файл класса Зашифрованный Файл
 *
 * Данный класс наследуется от обычного Файла
 * */
#ifndef FILESYSTEM_ENCRYPTFILE_H
#define FILESYSTEM_ENCRYPTFILE_H
#include "File.h"
#include <string>
#include <set>
#include "User.h"

namespace System{
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Зашифрованный Файл
     *
     * Класс для описания характеристик папок, лежащих на диске
     * */
    class EncryptFile : public File {
    private:
        // set of user ids
        std::set<size_t> tabelOfAccessUsers; ///< таблица пользователей с доступом к файлу
    public:
        /**
         * \brief стандартный конструктор
         *
         * @param ownerId идентификатор пользователя
         * @param uoPermissions права доступа для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
         */
        EncryptFile(size_t ownerId, unsigned int uoPermissions = 66);
        /**
         * \brief геттер для таблицы доступа
         *
         * @return таблицу доступа
         */
        std::set<size_t> getTableOfAccess() const { return tabelOfAccessUsers; }
        // setters
        // additional methods
        /**
         * \brief добавить пользователя по его идентификатору в таблицу доступа
         *
         * @param userId идентификатор пользователя
         * \throw invalid_argument такого пользователя нет в таблице
         * пользователей файловой системы
         */
        void addUserToAccess(size_t userId);
    };
}

#endif //FILESYSTEM_ENCRYPTFILE_H
