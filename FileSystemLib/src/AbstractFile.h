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
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс АбстрактныйФайл
     *
     * Класс созданный для удобства в иерархии классов,
     * чтобы от него наследовались классы Файл и Директория
     * */
    class AbstractFile {
    protected:
        unsigned int ownerId; ///< идентификатор пользователя
        size_t size; ///< размер файла в байтах
        Permissions uoPermissions; ///< права доступа для user & others
    public:
        /**
         * \brief конструктор используемый для инициализации части полей
         *
         * @param ownerId идентификатор пользователя
         * @param uoPermissions права доступа для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
         */
        AbstractFile(unsigned int ownerId, unsigned int uoPermissions = 66);
        virtual ~AbstractFile();
        /**
         * \brief сеттер, устанавливающий новые права доступа
         *
         * @param codePermissions новые права доступа для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
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
        unsigned int getOwner() const { return ownerId; }
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
        virtual std::string information () const = 0;
//        void edit();
        /**
         * \brief проверка прав доступа для взаимодействия с объектом
         *
         * @param currUserId идентификатор текущего пользователя файловой системы
         * @param parameter операция которую хотят проделать над файлом: rwx
         * \throw invalid_argument в случае неверной операции (не rwx)
         * @return подтверждение или отказ к выполнению операции
         */
        bool checkPermission(unsigned int currUserId, const std::string& parameter) const;
    };
}
/*TODO
 * 1. Добавить виртуальный деструктор
 * 2. Добавить
 * */

#endif //FILESYSTEM_ABSTRACTFILE_H
