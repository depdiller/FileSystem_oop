//
// Created by stani on 06.12.2021.
//
#include "Descriptor.h"

namespace System {
    Descriptor::Descriptor(std::string streamName, int indexInTable) {
        this->streamName;
        virtualAddress = standardOffset * indexInTable;
    }

    Descriptor::Descriptor(const std::string &streamName) {
        this->streamName = streamName;
        virtualAddress = standardOffset;
    }

    Descriptor &Descriptor::setStreamName(std::string newName) {
        streamName = std::move(newName);
        return *this;
    }

    bool Descriptor::operator<(const Descriptor &another) const {
        return this->streamName < another.streamName;
    }

    bool Descriptor::operator<(const std::string &name) const {
        return this->streamName < name;
    }

    bool Descriptor::operator==(const std::string &name) const {
        return this->streamName == name;
    }

    bool Descriptor::operator!=(const std::string &name) const {
        return this->streamName != name;
    }
}

