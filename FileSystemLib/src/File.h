//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

#include "AbstractFile.h"
#include <vector>

namespace System {
    class File : public AbstractFile {
    protected:
        std::string dateAndTime;
        std::vector<Descriptor> TableOfStreams;
    public:
        File(unsigned int );
        void getDateAndTime;

        void OpenFile();

        void getStreams;
        void virtualInformation;
    };
}

#endif //FILESYSTEM_FILE_H
