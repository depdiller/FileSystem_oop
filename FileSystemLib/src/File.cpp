#include "File.h"
#include "FileSystem.h"
#include <algorithm>

#include <utility>

namespace System {
    File::File(unsigned int fileVirtualAdrs, unsigned int ownerId, unsigned int uoPermissions) : AbstractFile(ownerId,
                                                                                                        uoPermissions) {
        TableOfStreams.insert(Descriptor("MAIN", fileVirtualAdrs));
    }

    File &File::setDateAndTime(std::string updateTime) {
        dateAndTime = std::move(updateTime);
        return *this;
    }

    /** currentSystemDisk придет при открытии файла через директорию, у которой будет
     * доступ к системе.
    */
    std::pair<FILE *, const std::string &>
    File::open(FILE *currentSystemDisk, unsigned int currUserId, const std::string &parameter) {
        if (this->checkPermission(currUserId, parameter)) {
            FILE *tmpCopy = currentSystemDisk;
            unsigned int offset = this->TableOfStreams.find(std::string("MAIN"))->getVirtualAddress();
            std::fseek(tmpCopy, offset, SEEK_CUR);
            return std::make_pair(tmpCopy, parameter);
        } else
            throw std::invalid_argument("no access to such operation");
    }

    void File::writeToFile(std::pair<FILE *, const std::string &> streamAndOperation, const std::string &data) {
        if (streamAndOperation.second == "w") {
            if (this->size + data.size() <= stdSize)
                std::fwrite(data.c_str(), sizeof(char), data.size(), streamAndOperation.first);
            else
                throw std::invalid_argument("exceeded standard size of file");
        } else
            throw std::invalid_argument("incorrect operation");
    }

    std::string File::readFile(std::pair<FILE *, const std::string &> streamAndOperation, size_t stringLength) {
        if (streamAndOperation.second == "w") {
            std::string myString(stringLength, '\0');
            std::fread(&myString[0], sizeof(char), stringLength, streamAndOperation.first);
            return myString;
        } else
            throw std::invalid_argument("incorrect operation");
    }

    void File::cat(FILE *ptrFromOpen) {
        if (ptrFromOpen != nullptr) {
            std::string myString(this->size, '\0');
            fread(&myString[0], sizeof(char), this->size, ptrFromOpen);
            std::cout << myString;
        } else
            throw std::invalid_argument("stream is not attached to file");
    }

    void File::editFile(FILE *ptrFromOpen, const std::string &toAdd) {
        if (ptrFromOpen != nullptr)
            std::fwrite(toAdd.c_str(), sizeof(char), toAdd.size(), ptrFromOpen);
        else
            throw std::invalid_argument("stream is not attached to file");
    }

    void File::information() const {
        std::cout << this->ownerId << std::endl <<
                  this->dateAndTime << std::endl <<
                  this->size << std::endl << std::endl;
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