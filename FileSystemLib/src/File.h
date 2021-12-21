/**
 * \file
 * \brief Заголовочный файл класса Обычного Файла
 *
 * Данный класс описывает поведение Файла в файловой системе,
 * также является родительским для Зашифрованного Файла
 * */
#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include "AbstractFile.h"
#include "Descriptor.h"
#include <set>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

namespace System {
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Файл
     *
     * Описывает работу файла на диске
     * */
    class File : public AbstractFile {
    protected:
        std::string dateAndTime; ///< дата и время последнего изменения файла
        std::set<Descriptor> TableOfStreams; ///< таблица ассоциированных с файлом потоков
    public:
        /**
         * \brief стандартный конструктор
         *
         * @param ownerId идентификатор пользователя
         * @param uoPermissions права доступа для user & others
         * \throw invalid_argument в случае некорректного параметра прав доступа
         */
        File(size_t ownerId, unsigned int uoPermissions = 66);
        /**
         * \brief сеттер для даты и времени последнего изменения файла
         *
         * @param updateTime новые дата и время
         * @return ссылка на измененный объект
         */
        File &setDateAndTime(std::string updateTime);
        /**
         * \brief геттер для даты и времени последних изменений
         * @return дата и время последних изменений в строковом формате
         */
        std::string getDateAndTime() { return this->dateAndTime; }
        /**
         * \brief геттер для потока потоков, ассоциированных с файлом
         * @return таблица потоков
         */
        std::set<Descriptor> getStreams() { return this->TableOfStreams; }
        // additional
        // parameter = "r"/"w"/"rw"

        /**
         * \brief открывает файл в определенном потоке
         *
         * @param currSystemDisk указатель на текущий файл-диск
         * @param currUserId идентификатор текущего пользователя
         * @param parameter операция для которой открывается (r w rw)
         * @param streamName имя потока
         * \throw invalid_argument отказ в доступе
         * @return указатель на файл в потоке
         */
        FILE *open(FILE *currSystemDisk, size_t currUserId, const std::string& parameter, const std::string& streamName = "MAIN");
        /**
         * \brief закрывает файл
         *
         * @param currSystemDisk указатель на текущий файл-диск
         * @return указатель на начало файла-диска
         */
        FILE *close(FILE *currSystemDisk);
        /**
         * \brief записать информацию в файл
         *
         * @param ptrFromOpen указатель на файл в потоке
         * @param data информация для записи в файл
         * \throw invalid_argument файл не открыт ни в каком потоке
         */
        void writeToFile(FILE *ptrFromOpen, const std::string& data);
        // stringLength ~= size of bytes
        /**
         * \brief считывание информации из файла
         *
         * @param ptrFromOpen указатель на файл в потоке
         * @param stringLength размер прочитанной информации
         * \throw invalid_argument файл не открыт ни в каком потоке
         * @return строка с информацией из файла
         */
        std::string readFile(FILE *ptrFromOpen, size_t stringLength);
        /**
         * \brief вывод содержимого файла на экран
         *
         * @param ptrFromOpen указатель на файл в потоке
         * \throw invalid_argument файл не открыт ни в каком потоке
         */
        void cat(FILE *ptrFromOpen);
        // write additional line to file
        /**
         * \brief изменить содержимое файла (добавить информацию)
         * @param ptrFromOpen указатель на файл в потоке
         * @param toAdd информация для добавления
         * \throw invalid_argument файл не открыт ни в каком потоке
         */
        void editFile(FILE *ptrFromOpen, const std::string &toAdd);
        /**
         * \brief перегрузка родительского метода, выводит информацию о папке
         */
        void information () const override;
    };

    // additional outside functions
    /**
     * \brief получить текущее системное время
     * @return текущие дата и время в строковом формате
     */
    std::string currentDateTime();
}
#endif //FILESYSTEM_FILE_H

/*TODO
 * 1. Переписать open, чтобы не использовал преобразование
 * unsigned int -> size_t*/
