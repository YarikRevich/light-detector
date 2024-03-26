#include "read_buffer.h"

ReadBuffer::ReadBuffer() : index(0), size(0), bytes{0U} {
}

void ReadBuffer::set_data(uint8_t *src1, const uint32_t src2) {
    this->bytes = src1;
    this->size = src2;
}

uint32_t ReadBuffer::get_size() const {
    return index;
}

uint32_t ReadBuffer::get_max_size() const {
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
