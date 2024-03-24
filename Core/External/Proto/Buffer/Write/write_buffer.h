#ifndef LIGHT_DETECTOR_WRITE_BUFFER_H
#define LIGHT_DETECTOR_WRITE_BUFFER_H

#include <WriteBufferInterface.h>
#include <stdio.h>

template<uint32_t BUFFER_SIZE>
class WriteBuffer : public EmbeddedProto::WriteBufferInterface {
public:
    WriteBuffer();

    virtual ~WriteBuffer() = default;

    void clear() override;

    uint32_t getSize() const override {
        return bytes_used_;
    }

    uint32_t getMaxSize() const override {
        return BUFFER_SIZE;
    }

    uint32_t get_available_size() const override {
        return -bytes_used_;
    }

    bool push(const uint8_t byte) override {
        bool result = BUFFER_SIZE > bytes_used_;
        if (result) {
            bytes_[bytes_used_] = byte;
            ++bytes_used_;
        }
        return result;
    }

    bool push(const uint8_t *bytes, const uint32_t length) override {
        bool result = BUFFER_SIZE >= (bytes_used_ + length);
        if (result) {
            memcpy(bytes_ + bytes_used_, bytes, length);
            bytes_used_ += length;
        }
        return result;
    }

private:
    uint32_t bytes_used_;
    uint8_t bytes_[BUFFER_SIZE];
};

#endif //LIGHT_DETECTOR_WRITE_BUFFER_H
