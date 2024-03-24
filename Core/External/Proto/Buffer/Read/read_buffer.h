#ifndef LIGHT_DETECTOR_READ_BUFFER_H
#define LIGHT_DETECTOR_READ_BUFFER_H

#include <stdio.h>
#include "ReadBufferInterface.h"

class ReadBuffer : public EmbeddedProto::ReadBufferInterface {
public:
    ReadBuffer();

    virtual ~ReadBuffer() = default;

    void setData(uint8_t *bytes, const uint32_t size);

    uint32_t getSize() const;

    uint32_t getMaxSize() const;

    bool peek(uint8_t &byte) const override;

    bool advance() override;

    bool advance(const uint32_t N) override;

    bool pop(uint8_t &byte) override;

private:
    uint32_t index;
    uint32_t size;
    uint8_t *bytes;
};

#endif //LIGHT_DETECTOR_READ_BUFFER_H
