#ifndef LIGHT_DETECTOR_READ_BUFFER_H
#define LIGHT_DETECTOR_READ_BUFFER_H

#include <stdio.h>
#include "ReadBufferInterface.h"

/**
 * Represents read buffer implementation for protocol buffers serialization.
 */
class ReadBuffer : public EmbeddedProto::ReadBufferInterface {
public:
    ReadBuffer();

    virtual ~ReadBuffer() = default;

    /**
     * Sets given buffer data.
     *
     * @param src1 - given buffer source.
     * @param src2 - given buffer source size.
     */
    void set_data(uint8_t *src1, uint32_t src2);

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
     * Represents current size of the buffer.
     */
    uint32_t index;

    /**
     * Represents max size of the buffer.
     */
    uint32_t size;

    /**
     * Represents current buffer data.
     */
    uint8_t *bytes;
};

#endif //LIGHT_DETECTOR_READ_BUFFER_H
