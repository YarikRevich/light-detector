#ifndef LIGHT_DETECTOR_REQUEST_BUFFER_H
#define LIGHT_DETECTOR_REQUEST_BUFFER_H

#include "ReadBufferInterface.h"

#include <cstdio>

#define DEFAULT_REQUEST_BUFFER_SIZE 6

/**
 * Represents request buffer implementation for protocol buffers serialization.
 *
 * @tparam BUFFER_SIZE - given size of the internal request buffer.
 */
template<uint32_t BUFFER_SIZE>
class RequestBuffer : public EmbeddedProto::ReadBufferInterface {
public:
    RequestBuffer();

    ~RequestBuffer() override = default;

//    /**
//     * Retrieves raw buffer used for direct data injection.
//     *
//     * @return raw buffer reference.
//     */
//    uint8_t* get_raw_buffer();

    /**
     * Retrieves raw buffer used for direct data injection.
     *
     * @return raw buffer reference.
     */
    void set_raw_buffer(uint8_t* src);

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    [[nodiscard]] uint32_t get_size() const override;

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    [[nodiscard]] uint32_t get_max_size() const override;

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    bool peek(uint8_t &byte) const override;

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    bool advance() override;

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    bool advance(const uint32_t N) override;

    /**
     * @see EmbeddedProto::ReadBufferInterface
     */
    bool pop(uint8_t &byte) override;

private:
    /**
     * Represents current buffer cursor position.
     */
    uint32_t index;

    /**
     * Represents max size of the buffer.
     */
    uint32_t size = BUFFER_SIZE;

    /**
     * Represents current buffer data.
     */
    uint8_t *bytes[BUFFER_SIZE];
};

#endif //LIGHT_DETECTOR_REQUEST_BUFFER_H
