#include "response_buffer.h"

ResponseBuffer::ResponseBuffer() : index(0), size(0), bytes{nullptr} {
}

uint8_t *ResponseBuffer::get_raw_buffer() {
    return bytes;
}

void ResponseBuffer::clear() {
    index = 0;
}

uint32_t ResponseBuffer::get_size() const {
    return index;
}

uint32_t ResponseBuffer::get_max_size() const {
    return size;
}

void ResponseBuffer::set_max_size(uint32_t value) {
    this->size = value;
}

uint32_t ResponseBuffer::get_available_size() const {
    return -index;
}

bool ResponseBuffer::push(const uint8_t byte) {
    bool result = size > index;
    if (result) {
        bytes[index] = byte;
        ++index;
    }
    return result;
}

bool ResponseBuffer::push(const uint8_t *src, const uint32_t length) {
    bool result = size >= (index + length);
    if (result) {
        memcpy(bytes + index, src, length);
        index += length;
    }
    return result;
}