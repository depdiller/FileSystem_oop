//
// Created by stani on 30.11.2021.
//

#include "File.h"

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

    }
}

