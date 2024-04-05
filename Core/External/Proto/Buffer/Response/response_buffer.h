#ifndef LIGHT_DETECTOR_RESPONSE_BUFFER_H
#define LIGHT_DETECTOR_RESPONSE_BUFFER_H

#include "WriteBufferInterface.h"

#include <cstdio>
#include <cstring>

#define DEFAULT_RESPONSE_BUFFER_SIZE 6

/**
 * Represents response buffer implementation for protocol buffers serialization.
 *
 * @tparam BUFFER_SIZE - given size of the internal response buffer.
 */
template<uint32_t BUFFER_SIZE>
class ResponseBuffer : public EmbeddedProto::WriteBufferInterface {
public:
    ResponseBuffer();

    ~ResponseBuffer() override = default;

    /**
     * Retrieves raw buffer used for direct data injection.
     *
     * @return raw buffer reference.
     */
    uint8_t *get_raw_buffer();

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    void clear() override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_size() const override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_max_size() const override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_available_size() const override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    bool push(const uint8_t byte) override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    bool push(const uint8_t *src, const uint32_t length) override;

private:
    /**
     * Represents amount of currently used bytes by buffer.
     */
    uint32_t bytes_used;

    /**
     * Represents current buffer data.
     */
    uint8_t *bytes[BUFFER_SIZE];
};

#endif //LIGHT_DETECTOR_RESPONSE_BUFFER_H
