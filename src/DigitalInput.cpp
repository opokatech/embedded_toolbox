#include "DigitalInput.hpp"

namespace ET
{
    DigitalInput::DigitalInput(bool initialValue) : active_(initialValue), rawActiveValue_(false), changed_(false) {}

    bool DigitalInput::isActive() const
    {
        return active_;
    }

    uint16_t DigitalInput::getMinRepeatedSamples() const
    {
        return minRepeatedSamples_;
    }

    bool DigitalInput::hasChanged() const
    {
        return changed_;
    }

    void DigitalInput::setActive(bool newValue)
    {
        changed_ = false;
        if (newValue == rawActiveValue_)
        {
            if (repeatedSamples_ < minRepeatedSamples_)
            {
                repeatedSamples_ += 1;
            }
        }
        else
        {
            rawActiveValue_  = newValue;
            repeatedSamples_ = 0;
        }

        if ((active_ != rawActiveValue_) && (repeatedSamples_ >= minRepeatedSamples_))
        {
            active_  = rawActiveValue_;
            changed_ = true;
        }
    }

    void DigitalInput::setMinRepeatedSamples(uint16_t minRepeatedSamples)
    {
        minRepeatedSamples_ = minRepeatedSamples;
    }
} // namespace ET
