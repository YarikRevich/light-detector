#include "response_buffer.h"

template<uint32_t BUFFER_SIZE>
ResponseBuffer<BUFFER_SIZE>::ResponseBuffer() : bytes_used(0), bytes{0} {
}

template<uint32_t BUFFER_SIZE>
uint8_t *ResponseBuffer<BUFFER_SIZE>::get_raw_buffer() {
    return bytes;
}

template<uint32_t BUFFER_SIZE>
void ResponseBuffer<BUFFER_SIZE>::clear() {
    bytes_used = 0;
}

template<uint32_t BUFFER_SIZE>
uint32_t ResponseBuffer<BUFFER_SIZE>::get_size() const {
    return bytes_used;
}

template<uint32_t BUFFER_SIZE>
uint32_t ResponseBuffer<BUFFER_SIZE>::get_max_size() const {
    return BUFFER_SIZE;
}

template<uint32_t BUFFER_SIZE>
uint32_t ResponseBuffer<BUFFER_SIZE>::get_available_size() const {
    return -bytes_used;
}

template<uint32_t BUFFER_SIZE>
bool ResponseBuffer<BUFFER_SIZE>::push(const uint8_t byte) {
    bool result = BUFFER_SIZE > bytes_used;
    if (result) {
        bytes[bytes_used] = byte;
        ++bytes_used;
    }
    return result;
}

template<uint32_t BUFFER_SIZE>
bool ResponseBuffer<BUFFER_SIZE>::push(const uint8_t *src, const uint32_t length) {
    bool result = BUFFER_SIZE >= (bytes_used + length);
    if (result) {
        memcpy(bytes + bytes_used, src, length);
        bytes_used += length;
    }
    return result;
}