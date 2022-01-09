/**
 * \file
 * \brief Заголовочный файл класса Прав Доступа
 *
 * Данный класс описывает поведение Прав Доступа
 * */
#ifndef FILESYSTEM_PERMISSIONS_H
#define FILESYSTEM_PERMISSIONS_H
#include <array>

namespace System {
    /**
     * \brief вспомогательная структура для
     * удобства проверки на определенную операцию (r w x)
     */
    struct rwx {
    private:
        bool read; ///< чтение
        bool write; ///< изменение
        bool execute; ///< открыть
    public:
        /**
         * \brief стандартный конструктор
         * @param codePermission код для прав (4-r 2-w 1-x)
         * \throw invalid_argument некорректный код прав
         */
        explicit rwx(unsigned int codePermission = 6);
        /**
         * \brief проверка на чтение
         * @return можно или нет
         */
        bool isReadable() const { return read; }
        /**
         * \brief проверка на запись
         * @return можно или нет
         */
        bool isWritable() const { return write; }
        /**
         * \brief проверка на исполнение
         * @return можно или нет
         */
        bool isExecutable() const { return execute; }
        std::string inText() const;
    };

    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Права Доступ
     *
     *
     * */
    class Permissions {
    private:
        std::array<rwx, 2> uoPermissions; ///< массив с правами доступа
    public:
        /**
         * \brief стандартный конструктор
         * @param codePermissions права доступа для user & others
         * \throw invalid_argument некорректный код для прав доступа
         */
        explicit Permissions(unsigned int codePermissions = 66);
        /**
         * \brief сеттер для прав доступа
         * @param codePermission код доступа
         * \throw invalid_argument некорректный код для прав доступа
         * @return ссылка на измененный объект
         */
        Permissions& setPermissions(unsigned int codePermission);
        /**
         * \brief геттер для прав доступа
         * @return массив из прав доступа для user & others
         */
        std::array<rwx, 2> getPermissions() const { return uoPermissions; }
        Permissions &operator=(const Permissions &other);
        std::string info() const;
    };
}

#endif //FILESYSTEM_PERMISSIONS_H
