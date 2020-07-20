#pragma once

#include <stdint.h>

/* Digital input debouce class.
 *
 * If a new input value is repeated at least a given amount of times then
 * it becomes a new output value.
 *
 */

namespace ET
{
    class DigitalInput
    {
    public:
        DigitalInput(bool initialValue);

        bool     isActive() const;
        uint16_t getMinRepeatedSamples() const;
        bool     hasChanged() const;

        void setActive(bool newValue);
        void setMinRepeatedSamples(uint16_t minRepeatedSamples);

    private:
        bool     active_ : 1;
        bool     rawActiveValue_ : 1;
        bool     changed_ : 1;
        uint16_t repeatedSamples_    = 0;
        uint16_t minRepeatedSamples_ = 0;
    };
} // namespace ET
