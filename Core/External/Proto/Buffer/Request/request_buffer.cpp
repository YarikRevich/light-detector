#include "request_buffer.h"

template<uint32_t BUFFER_SIZE>
RequestBuffer<BUFFER_SIZE>::RequestBuffer() : index(0), size(0), bytes{0U} {
}

template<uint32_t BUFFER_SIZE>
uint8_t * RequestBuffer<BUFFER_SIZE>::get_raw_buffer() {
    return this->bytes;
}

template<uint32_t BUFFER_SIZE>
uint32_t RequestBuffer<BUFFER_SIZE>::get_size() const {
    return index;
}

template<uint32_t BUFFER_SIZE>
uint32_t RequestBuffer<BUFFER_SIZE>::get_max_size() const {
    return size;
}

template<uint32_t BUFFER_SIZE>
bool RequestBuffer<BUFFER_SIZE>::peek(uint8_t &byte) const {
    bool result = this->index < this->size;
    if (result) {
        byte = this->bytes[this->index];
    }

    return result;
}

template<uint32_t BUFFER_SIZE>
bool RequestBuffer<BUFFER_SIZE>::advance() {
    const bool result = this->index < this->size;
    if (result) {
        ++this->index;
    }
    return result;
}

template<uint32_t BUFFER_SIZE>
bool RequestBuffer<BUFFER_SIZE>::advance(const uint32_t src) {
    this->index += src;
    const bool result = this->index < this->size;
    if (result) {
        this->index = this->size;
    }

    return result;
}

template<uint32_t BUFFER_SIZE>
bool RequestBuffer<BUFFER_SIZE>::pop(uint8_t &byte) {
    bool result = this->index < this->size;
    if (result) {
        byte = this->bytes[this->index];
        ++this->index;
    }

    return result;
}
