//
// Created by stani on 30.11.2021.
//

#include "File.h"
#include "FileSystem.h"

#include <utility>

namespace System {
    File::File(size_t ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions) {
        TableOfStreams.insert(Descriptor("MAIN", 1));
    }

    std::string currentDateTime() {
        time_t now = time(nullptr);
        struct tm tstruct{};
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }

    File &File::setDateAndTime(std::string updateTime) {
        dateAndTime = std::move(updateTime);
        return *this;
    }

    void File::information() const {
        std::cout << this->ownerId << std::endl <<
                  this->dateAndTime << std::endl <<
                  this->size << std::endl << std::endl;
    }

    FILE *File::open(FILE *currSystemDisk, size_t currUserId, const std::string &parameter, const std::string &streamName) {
        if (this->checkPermission(currUserId, parameter)) {
            std::set<Descriptor>::iterator it;
            it = TableOfStreams.find(streamName);
            if (it != TableOfStreams.end()) {
                std::fseek(currSystemDisk, standardOffset + (unsigned int)size, SEEK_CUR);
                return currSystemDisk;
            } else
                return nullptr;
        } else
            throw std::invalid_argument("no access to such operation");
    }

    FILE *File::close(FILE *currSystemDisk) {
        return currSystemDisk;
    }

    void File::writeToFile(FILE *ptrFromOpen, const std::string &data) {
        if (ptrFromOpen != nullptr)
            std::fwrite(data.c_str(), sizeof(char), data.size(), ptrFromOpen);
        else
            throw std::invalid_argument("stream is not attached to any file");
    }

    std::string File::readFile(FILE *ptrFromOpen, size_t stringLength) {
        if (ptrFromOpen != nullptr) {
            std::string myString(stringLength, '\0');
            std::fread(&myString[0], sizeof(char), stringLength, ptrFromOpen);
            return myString;
        } else
            throw std::invalid_argument("stream is not attached to file");
    }

    void File::cat(FILE *ptrFromOpen) {
        if (ptrFromOpen != nullptr) {
            std::string myString(this->size, '\0');
            fread(&myString[0], sizeof(char), this->size, ptrFromOpen);
            std::cout << myString;
        }
        else
            throw std::invalid_argument("stream is not attached to file");
    }

    void File::editFile(FILE *ptrFromOpen, const std::string &toAdd) {
        if (ptrFromOpen != nullptr)
            std::fwrite(toAdd.c_str(), sizeof(char), toAdd.size(), ptrFromOpen);
        else
            throw std::invalid_argument("stream is not attached to file");
    }
}