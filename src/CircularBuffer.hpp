#pragma once

#include <stdint.h>

namespace ET
{
    /* Circular buffer with fixed capacity for given type.
     *
     * It allows pushing and poping to and from the buffer. Keeps count of the elements in the buffer.
     */
    template <uint16_t SIZE, typename T>
    class CircularBuffer
    {
    public:
        using valueType = T;

        constexpr uint16_t getCapacity() const
        {
            return SIZE;
        }

        constexpr uint16_t getSize() const
        {
            return size_;
        }

        void push(const T &v)
        {
            array_[pushPos_] = v;

            increase_index(pushPos_);

            if (size_ < SIZE)
            {
                size_ += 1;
            }
            else // we reached max
            {
                increase_index(popPos_);
            }
        }

        bool pop(T &v)
        {
            if (size_ < 1)
            {
                return false;
            }

            v = array_[popPos_];
            increase_index(popPos_);

            size_ -= 1;

            return true;
        }

    protected:
        T        array_[SIZE] = {};
        uint16_t size_        = 0;
        uint16_t pushPos_     = 0;
        uint16_t popPos_      = 0;

    private:
        void increase_index(uint16_t &idx)
        {
            idx += 1;
            if (idx == SIZE)
            {
                idx = 0;
            }
        }
    };
} // namespace ET
