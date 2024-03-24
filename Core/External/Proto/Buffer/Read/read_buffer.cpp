#include "read_buffer.h"

ReadBuffer::ReadBuffer() : index(0), size(0), bytes{0U} {
}

void ReadBuffer::setData(uint8_t *bytes, const uint32_t size) {
    this->bytes = bytes;
    this->size = size;
}

uint32_t ReadBuffer::getSize() const {
    return index;
}

uint32_t ReadBuffer::getMaxSize() const {
    return size;
}

bool ReadBuffer::peek(uint8_t &byte) const {
    bool result = this->index < this->size;
    if (result) {
        byte = this->bytes[this->index];
    }

    return result;
}

bool ReadBuffer::advance() {
    const bool result = this->index < this->size;
    if (result) {
        ++this->index;
    }
    return result;
}

bool ReadBuffer::advance(const uint32_t src) {
    this->index += src;
    const bool result = this->index < this->size;
    if (result) {
        this->index = this->size;
    }

    return result;
}

bool ReadBuffer::pop(uint8_t &byte) {
    bool result = this->index < this->size;
    if (result) {
        byte = this->bytes[this->index];
        ++this->index;
    }

    return result;
}
