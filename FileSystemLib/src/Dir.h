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
#include <map>

namespace System {
    /*виртуальные адреса папок - с начала файла, то есть потоки
     * начинаются с 1024 байта, а все пространство до этого выделяется
     * под директории и файлы*/
    const size_t bytesForDir = 16; ///< стандартное смещение дла расположения папок на диске(файле)

    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Директории
     *
     * Класс для описания характеристик папок, лежащих на диске
     * */
    class Dir : public AbstractFile {
    private:
        unsigned int virtualAddress; ///< виртуальный адрес папки

        /* описатель структуры каталога, в нее входят и подкаталоги
         * еще указатель на родительскую папку, потом указатель на
         * описатель этого файла */

        /**
         * таблица ассоциированных с директорией файлов
         * могут быть как файлы, так и поддиректории
         */
        std::map<std::pair<std::string, Dir*>, AbstractFile*> tableOfFiles;
    public:
        /**
         * \brief стандартный конструктор
         *
         * @param ownerId идентификатор владельца папки
         * @param uoPermissions набор разрешений для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
         */
        Dir(size_t ownerId, unsigned int uoPermissions = 66);
        /**
         * \brief вывести содержимое папки
         */
        void showContentDir();

            // fileOrDir = 'f' / 'd'
        /**
         * \brief создать поддиректорию или файл в текущей папке
         *
         * @param currUserId идентификатор текущего пользователя файловой системы
         * @param fileOrDir создать подкаталог или файл
         * @param name имя нового объекта
         * \throw invalid_argument при некорректном типе создаваемого объекта
         */
        void create(size_t currUserId, char fileOrDir, const std::string& name);
        /**
         * \brief скопировать файл или подкаталог
         */
        void copy();
        /**
         * \brief переместить файл или подкаталог
         */
        void move();
        /**
         * \brief удалить файл или подкатолог
         */
        void deleteFile();
        /**
         * \brief перегрузка родительского метода, выводит информацию о папке
         */
        void information() const override;
    };
}

#endif //FILESYSTEM_DIR_H
