/**
 * \file
 * \brief Заголовочный файл класса Пользователя
 *
 * Данный класс описывает поведение Пользователя
 * */
#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H
#include "Dir.h"
#include <iostream>

namespace System {
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Пользователя
     *
     *
     */
    class User {
    private:
        size_t userId; ///< идентификатор пользователя
        std::string name; ///< имя пользователя
        size_t key; ///< ключ пользователя для шифрования файлов
    public:
        /**
         * \brief конструктор принимающий только имя пользователя
         * @param name имя пользователя
         */
        User(const std::string& name);
        /**
         * \brief конструктор принимающий имя пользователя и ключ для шифрования
         * @param name имя пользователя
         * @param key ключ для шифрования
         */
        User(const std::string& name, size_t key);
        /**
         * \brief сеттер для ключа
         * @param newKey новый ключ
         * @return ссылка на измененный объект
         */
        User& setKey(size_t newKey);
        /**
         * \brief сеттер для имени пользователя
         * @param newName новое имя пользователя
         * @return ссылка на измененный объект
         */
        User& setName(std::string newName);
        /**
         * \brief геттер для имени пользователя
         * @return имя пользователя в формате строки
         */
        std::string getName() const { return name; }
        /**
         * \brief геттер для идентификатора пользователя
         * @return идентификатор пользователя
         */
        size_t getUserId() const { return userId; }
        /**
         * \brief геттер для ключа шифрования пользователя
         * @return ключ шифрования пользователя
         */
        size_t getKey() const { return key; }
        /**
         * \brief перегруженный оператор равенства через объект класса
         * и строку с именем
         */
        bool operator==(const std::string &username) const;
        /**
         * \brief перегруженный оператор отрицания через объект класса
         * и строку с именем
         */
        bool operator!=(const std::string &username) const;
        /**
         * \brief перегруженный оператор сравнения через объекты класса
         */
        bool operator<(const User&) const;
        /**
         * \brief перегруженный оператор сравнения через объект класса
         * и строку с именем
         */
        bool operator<(const std::string &username) const;
        /**
         * \brief перегруженный оператор присваивания
         */
        User &operator=(const User&);
    };
}

/*TODO
 * 1. копирующий оператор проверить в файловой системе в login */

#endif //FILESYSTEM_USER_H
