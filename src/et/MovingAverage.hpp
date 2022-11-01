#pragma once

#include "CircularBuffer.hpp"

namespace ET
{
    template <uint16_t SIZE, typename T>
    class MovingAverage: public CircularBuffer<SIZE, T>
    {
    public:
        T getSum() const
        {
            return sum_;
        }

        T getAverage() const
        {
            // recalculate average if needs to be
            if (!averageIsValid_)
            {
                average_        = (this->size_ > 0) ? sum_ / this->size_ : 0;
                averageIsValid_ = true;
            }

            return average_;
        }

        void push(const T &v)
        {
            sum_ += v;
            averageIsValid_ = false;

            // if we are full then remove the last element from the sum
            if (this->size_ == SIZE)
            {
                sum_ -= this->array_[this->popPos_];
            }

            CircularBuffer<SIZE, T>::push(v);
        }

        bool pop(T &v)
        {
            if (this->size_ < 1)
            {
                return false;
            }

            sum_ -= this->array_[this->popPos_];
            averageIsValid_ = false;

            return CircularBuffer<SIZE, T>::pop(v);
        }

    private:
        T            sum_            = {};
        mutable T    average_        = {};
        mutable bool averageIsValid_ = false;
    };
} // namespace ET
