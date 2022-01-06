#include "Descriptor.h"
#include "File.h"

#include <utility>

namespace System {
    Descriptor::Descriptor(std::string streamName, unsigned int fileVirtualAdrs) : virtualAddress(fileVirtualAdrs){
        this->streamName = std::move(streamName);
    }

    Descriptor::Descriptor(const std::string &streamName) {
        this->streamName = streamName;
        virtualAddress = 0;
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

