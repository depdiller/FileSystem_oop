//
// Created by stani on 24.11.2021.
//

#ifndef FILESYSTEM_DESCRIPTOR_H
#define FILESYSTEM_DESCRIPTOR_H
#include <iostream>
#include <cstdio>

namespace System {
    const unsigned int standardOffset = 1024;

    class Descriptor {
    private:
        std::string streamName;
        unsigned int virtualAddress;
    public:
        // constructors
        /* indexInTable чтобы адрес каждого n-ого потока смешался
         * на n * 1024*/
        Descriptor(std::string streamName, int indexInTable);
        // getters
        std::string getStreamName() const { return streamName; };
        unsigned int getVirtualAddress() const { return virtualAddress; }
        // setters
        Descriptor &setStreamName(std::string newName);
        // operators
        bool operator<(const Descriptor&) const;
        bool operator==(const std::string&) const;
        bool operator!=(const std::string&) const;
    };
}

#endif //FILESYSTEM_DESCRIPTOR_H
