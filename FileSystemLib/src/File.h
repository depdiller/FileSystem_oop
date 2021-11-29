//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H

class File : AbstractFile{
protected:
    string dateAndTime;
    vector<Descriptor> TableOfStreams;
public:
    File();
    void getDateAndTime;
    void OpenFile();
    void getStreams;
    void virtualInformations;
};

#endif //FILESYSTEM_FILE_H
