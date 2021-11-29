//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DESCRIPTOR_H
#define FILESYSTEM_DESCRIPTOR_H

class Descriptor {
private:
    string streamName;
    int * virtAdr;
public:
    Descriptor(AbstractFile&);
};

#endif //FILESYSTEM_DESCRIPTOR_H
