/**
 * \file
 * \brief Заголовочный файл класса Обычного Файла
 *
 * Данный класс описывает поведение Файла в файловой системе,
 * также является родительским для Зашифрованного Файла.
 * Файлы в системе размещаются последовательно, под каждый
 * выделяется стандартный блок памяти, не превышая размер
 * которого, можно записывать данные в файл.
 * Когда создается файл, вместе с ним создается ассоциированный
 * дескриптор основного потока MAIN, где и лежит виртуальный адрес =
 * смещению от начала файла.
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
    const unsigned int stdSize = 1024;
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
        friend class Descriptor;
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
        File(unsigned int fileVirtualAdrs, unsigned int ownerId, unsigned int uoPermissions = 66);
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
        const std::set<Descriptor> &getStreams() { return this->TableOfStreams; }
        // additional
        // parameter = "r"/"w"/"rw"

        /**
         * \brief открывает файл в определенном потоке
         *
         * @param file указатель на текущий файл (смещение от диска)
         * @param currUserId идентификатор текущего пользователя
         * @param parameter операция для которой открывается (r w rw)
         * @param streamName имя потока
         * \throw invalid_argument отказ в доступе
         * @return указатель на файл в потоке
         */
        std::pair<FILE*, const std::string&> open(FILE *file, unsigned int currUserId, const std::string& parameter);
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
        void writeToFile(std::pair<FILE*, const std::string&>, const std::string &data);
        // stringLength ~= size of bytes
        /**
         * \brief считывание информации из файла
         *
         * @param ptrFromOpen указатель на файл в потоке
         * @param stringLength размер прочитанной информации
         * \throw invalid_argument файл не открыт ни в каком потоке
         * @return строка с информацией из файла
         */
        std::string readFile(std::pair<FILE*, const std::string&> streamAndOperation, size_t stringLength);
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
        std::string information () const override;
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
