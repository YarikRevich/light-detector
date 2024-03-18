#include <ReadBufferInterface.h>

namespace demo
{
    class ReadBuffer : public EmbeddedProto::ReadBufferInterface
    {
    public:
        ReadBuffer()
                : index_(0),
                  size_(0),
                  bytes_{0U}
        {

        }

        virtual ~ReadBuffer() = default;

        uint32_t get_size() const override
        {
            return index_;
        }

        uint32_t get_max_size() const override
        {
            return size_;
        }

        void set_demo_data(uint8_t* bytes, const uint32_t size)
        {
            bytes_ = bytes;
            size_ = size;
        }

        bool peek(uint8_t& byte) const override
        {
            bool result = index_ < size_;
            if(result)
            {
                byte = bytes_[index_];
            }
            return result;
        }

        bool advance() override
        {
            const bool result = index_ < size_;
            if(result)
            {
                ++index_;
            }
            return result;
        }

        bool advance(const uint32_t N) override
        {
            index_ += N;
            const bool result = index_ < size_;
            if(result)
            {
                index_ = size_;
            }
            return result;
        }

        bool pop(uint8_t& byte) override
        {
            bool result = index_ < size_;
            if(result)
            {
                byte = bytes_[index_];
                ++index_;
            }
            return result;
        }

    private:

        uint32_t index_;
        uint32_t size_;
        uint8_t* bytes_;

    };
}
