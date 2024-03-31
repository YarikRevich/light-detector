#ifndef LIGHT_DETECTOR_RESPONSE_BUFFER_H
#define LIGHT_DETECTOR_RESPONSE_BUFFER_H

#include <WriteBufferInterface.h>
#include <stdio.h>
#include <cstring>

/**
 * Represents response buffer implementation for protocol buffers serialization.
 *
 * @tparam BUFFER_SIZE
 */
template<uint32_t BUFFER_SIZE>
class ResponseBuffer : public EmbeddedProto::WriteBufferInterface {
public:
    ResponseBuffer();

    virtual ~ResponseBuffer() = default;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    void clear() override;

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_size() const override {
        return bytes_used;
    }

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_max_size() const override {
        return BUFFER_SIZE;
    }

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    [[nodiscard]] uint32_t get_available_size() const override {
        return -bytes_used;
    }

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    bool push(const uint8_t byte) override {
        bool result = BUFFER_SIZE > bytes_used;
        if (result) {
            bytes[bytes_used] = byte;
            ++bytes_used;
        }
        return result;
    }

    /**
     * @see EmbeddedProto::WriteBufferInterface
     */
    bool push(const uint8_t *bytes, const uint32_t length) override {
        bool result = BUFFER_SIZE >= (bytes_used + length);
        if (result) {
            memcpy(bytes, bytes + bytes_used, length);
            bytes_used += length;
        }
        return result;
    }

private:
    /**
     * Represents amount of currently used bytes by buffer.
     */
    uint32_t bytes_used;

    /**
     * Represents current buffer data.
     */
    uint8_t bytes[BUFFER_SIZE];
};

#endif //LIGHT_DETECTOR_RESPONSE_BUFFER_H
