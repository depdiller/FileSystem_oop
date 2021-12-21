/**
 * \file
 * \brief Заголовочный файл класса АбстрактныйФайл
 *
 * Данный абстрактный класс содержит общие поля и методы,
 * которые понадобятся в наследуемых от него классах: Файл и Директория
 * */
#ifndef FILESYSTEM_ABSTRACTFILE_H
#define FILESYSTEM_ABSTRACTFILE_H

#include "Permissions.h"
#include <iostream>

namespace System {
    /**
     * \brief Класс АбстрактныйФайл
     *
     * Класс созданный для удобства в иерархии классов,
     * чтобы от него наследовались классы Файл и Директория
     * */
    class AbstractFile {
    protected:
        size_t ownerId; ///< идентификатор пользователя
        size_t size; ///< размер файла в байтах
        Permissions uoPermissions; ///< права доступа для user & others
    public:
        /**
         * \brief конструктор используемый для инициализации части полей
         *
         * @param ownerId идентификатор пользователя
         * @param uoPermissions права доступа для user & others
         */
        explicit AbstractFile(size_t ownerId, unsigned int uoPermissions = 66);
        /**
         * \brief сеттер, устанавливающий новые права доступа
         *
         * @param codePermissions новые права доступа для user & others
         * */
        AbstractFile& setPermissions(unsigned int codePermissions);
        /**
         * \brief сеттер, устанавливающий новый размер объекта в байтах
         *
         * @param newSize новый размер объекта
         * @return указатель на измененный объект
         */
        AbstractFile& setSize(size_t newSize);
        /**
         * \brief геттер для получения идентификатора пользователя, связанного с объектом
         *
         * @return идентификатор пользователя
         */
        size_t getOwner() const { return ownerId; }
        /**
         * \brief геттер для получения текущего размера объекта
         *
         * @return размер объекта
         */
        size_t getSize() { return size; }
        /**
         * \brief геттер для получения прав доступа
         *
         * @return объект класса Permissions, в котором прописаны права объекта
         */
        Permissions getPermissions() const { return uoPermissions; }
        /**
         * \brief виртуальный метод, выводящий доступную классу информацию об объекте
         */
        virtual void information () const = 0;
//        void edit();
        /**
         * \brief проверка прав доступа для взаимодействия с объектом
         *
         * @param currUserId идентификатор текущего пользователя файловой системы
         * @param parameter операция которую хотят проделать над файлом: rwx
         * @return подтверждение или отказ к выполнению операции
         */
        bool checkPermission(size_t currUserId, const std::string& parameter) const;
    };
}
/*TODO
 * 1. Добавить виртуальный деструктор
 * 2. Добавить
 * */

#endif //FILESYSTEM_ABSTRACTFILE_H
