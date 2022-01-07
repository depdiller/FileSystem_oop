/**
 * \file
 * \brief Заголовочный файл класса Дексриптора потоков
 *
 * Данный абстрактный класс содержит общие поля и методы,
 * которые понадобятся в наследуемых от него классах: Файл и Директория.
 * Конструктор нового дескриптора вызывается из класса Файл при создании
 * нового потока.
 * */
#ifndef FILESYSTEM_DESCRIPTOR_H
#define FILESYSTEM_DESCRIPTOR_H
#include <iostream>
#include <cstdio>

namespace System {
    /**
     * \author Voronov Stanislav
     * \version 1.0
     * \date декабрь 2021
     *
     * \brief Класс Дескрипотор
     *
     * Класс для описания характеристик потоков, ассоциированных с файлами
     * */
    class File;
    class Descriptor {
    private:
        std::string streamName; ///< имя потока
        unsigned int virtualAddress; ///< виртуальный адрес потока
    public:
        /**
         * \brief конструктор, использующий имя файла и индекс в таблице потоков
         *
         * @param streamName имя потока
         * @param indexInTable индекс в таблице потоков для разделения
         * файла на потоки по 1024 байта
         */
        Descriptor(std::string streamName, unsigned int fileVirtualAdrs);
        /**
         * \brief конструктор использующий только имя потока
         * (дефолтный конструктор)
         *
         * @param streamName имя потока
         */
        Descriptor(const std::string& streamName);
        Descriptor &setVirtualAddress(unsigned int newAddress);
        /**
         * \brief геттер для имени потока
         *
         * @return строка с именем потока
         */
        std::string getStreamName() const { return streamName; };
        /**
         * \brief геттер для виртуального адреса
         *
         * @return виртуальный адрес
         */
        unsigned int getVirtualAddress() const { return virtualAddress; }
        /**
         * \brief сеттер для имени потока
         *
         * @param newName новое имя потока
         * @return ссылка на измененный объект
         */
        Descriptor &setStreamName(std::string newName);
        /**
         * \brief перегруженный оператор сравнения через объекты класса
         */
        bool operator<(const Descriptor&) const;
        /**
         * \brief перегруженный оператор сравнения через объект класса
         * и строку с именем
         */
        bool operator<(const std::string&) const;
        bool operator<(std::string &&otherName) const {
            return this->streamName < otherName;
        }
        /**
         * \brief перегруженный оператор равенства через объект класса
         * и строку с именем
         */
        bool operator==(const std::string&) const;
        /**
         * \brief перегруженный оператор отрицания через объект класса
         * и строку с именем
         */
        bool operator!=(const std::string&) const;
    };
}


#endif //FILESYSTEM_DESCRIPTOR_H
