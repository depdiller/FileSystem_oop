#include "File.h"
#include "FileSystem.h"
#include <algorithm>
#include <iostream>
#include <utility>

namespace System {
    File::File(unsigned int fileVirtualAddress, unsigned int ownerId, unsigned int uoPermissions) : AbstractFile(ownerId,
                                                                                                        uoPermissions) {
        TableOfStreams.insert(Descriptor("MAIN", fileVirtualAddress));
    }

    File &File::setDateAndTime(std::string updateTime) {
        dateAndTime = std::move(updateTime);
        return *this;
    }

    /** currentSystemDisk придет при открытии файла через директорию, у которой будет
     * доступ к системе.
    */
    FILE *File::open(FILE *currentSystemDisk, unsigned int currUserId, const std::string &parameter) {
        if (checkPermission(currUserId, parameter)) {
            FILE *tmpCopy = currentSystemDisk;
            unsigned int offset = this->TableOfStreams.find(std::string("MAIN"))->getVirtualAddress();
            std::fseek(tmpCopy, offset, SEEK_SET);
            return tmpCopy;
        }
        else
            throw std::invalid_argument("No access to open file");
    }

    void File::writeToFile(FILE *openedStream, const std::string &data) {
        if (openedStream != nullptr) {
            size = 0;
            if (size + data.size() <= stdSize) {
                size_t f = std::fwrite(data.c_str(), 1, data.size(), openedStream);
                if (f != data.size())
                    throw std::invalid_argument("Error during fwrite");
                size += data.size();
            }
            else
                throw std::invalid_argument("Exceeded standard size of file. Cannot write to file");
        }
        else {
            throw std::invalid_argument("Stream is corrupted");
        }
    }

    std::string File::readFile(FILE * openedStream, unsigned int stringLength) {
        if (openedStream != nullptr) {
            if (stringLength > size) {
                throw std::invalid_argument("Exceeded size of file");
            } else {
                std::string myString(stringLength, '\0');
                size_t f = std::fread(&myString[0], 1, (size_t)stringLength, openedStream);
                if (f != stringLength)
                    throw std::invalid_argument("Error during fread");
                return myString;
            }
        }
        else {
            throw std::invalid_argument("Stream is corrupted");
        }
    }

    std::string File::cat(FILE *openedStream) {
        if (openedStream != nullptr) {
            std::string myString(size, '\0');
            size_t f = std::fread(&myString[0], 1, (size_t) size, openedStream);
            if (f != (size_t)size)
                throw std::invalid_argument("Error during fread");
            return myString;
        }
        else {
            throw std::invalid_argument("Stream is corrupted");
        }
    }

    void File::editFile(FILE *openedStream, const std::string &toAdd) {
        if (openedStream != nullptr) {
            int status = std::fseek(openedStream, size, SEEK_CUR);
            if (status != 0) {
                throw std::invalid_argument("Error in fseek");
            }
            size_t f = std::fwrite(toAdd.c_str(), 1, toAdd.size(), openedStream);
            if (f != toAdd.size())
                throw std::invalid_argument("Error during fread");
            size += toAdd.size();
        }
        else {
            throw std::invalid_argument("Stream is corrupted");
        }
    }

    std::string File::information() const {
        char buff[100];
        snprintf(buff, sizeof(buff), "OwnerId: %d, last changes: %s, size: %zu",
                 ownerId, this->dateAndTime.c_str(), size);
        std::string buffAsStdStr = buff;
        return buff;
    }

    File &File::operator=(const File &other) {
        if (this != &other) {
            this->uoPermissions = other.uoPermissions;
            this->size = other.size;
            this->ownerId = other.ownerId;
        }
        return *this;
    }

    File::File() : AbstractFile(), TableOfStreams(), dateAndTime() {}

    File &File::setVritualAddress(unsigned int newAddress) {
//        auto it = TableOfStreams.find(std::string("MAIN"));
//        it->getVirtualAddress() = newAddress;
        return *this;
    }

    std::string currentDateTime() {
        time_t now = time(nullptr);
        struct tm tstruct{};
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
}