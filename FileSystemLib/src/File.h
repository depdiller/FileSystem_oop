//
// Created by stani on 24.11.2021.
//

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
    class File : public AbstractFile {
    protected:
        std::string dateAndTime;
        std::set<Descriptor> TableOfStreams;
    public:
        // constructors
        File(size_t ownerId, unsigned int uoPermissions = 66);
        // setters
        File &setDateAndTime(std::string updateTime);
        // getters
        std::string getDateAndTime() { return this->dateAndTime; }
        std::set<Descriptor> getStreams() { return this->TableOfStreams; }
        // additional
            // parameter = "r"/"w"/"rw"
        FILE *open(FILE *currSystemDisk, size_t currUserId, const std::string& parameter, const std::string& streamName = "MAIN");
        FILE *close(FILE *currSystemDisk);
        void writeToFile(FILE *ptrFromOpen, const std::string& data);
            // stringLength ~= size of bytes
        std::string readFile(FILE *ptrFromOpen, size_t stringLength);
        void cat(FILE *ptrFromOpen);
            // write additional line to file
        void editFile(FILE *ptrFromOpen, const std::string &toAdd);
        void information () const override;
    };

    // additional outside functions
    std::string currentDateTime();
}
#endif //FILESYSTEM_FILE_H

/*TODO
 * 1. Переписать open, чтобы не использовал преобразование
 * unsigned int -> size_t*/
