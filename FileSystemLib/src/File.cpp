//
// Created by stani on 30.11.2021.
//

#include "File.h"
#include "FileSystem.h"

#include <utility>

namespace System {
    File::File(size_t ownerId, unsigned int uoPermissions) : AbstractFile(ownerId, uoPermissions){
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

    void File::open(const std::string& parameter, const std::string& streamName) {
        if (this->checkPermission(parameter)) {
            std::set<Descriptor>::iterator it;
            it = TableOfStreams.find(streamName);
        }
        else
            throw std::invalid_argument("no access to such operation");
    }

}

