//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DESCRIPTOR_H
#define FILESYSTEM_DESCRIPTOR_H
#include <iostream>

class Descriptor {
private:
    std::string streamName;
    unsigned int virtualAddress;
public:
    Descriptor(AbstractFile&);
};

#endif //FILESYSTEM_DESCRIPTOR_H
