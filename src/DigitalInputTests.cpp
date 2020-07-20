#include "catch.hpp"

#include "DigitalInput.hpp"

TEST_CASE("DigitalInput")
{
    // common
    ET::DigitalInput di(false);
    REQUIRE_FALSE(di.isActive());

    ET::DigitalInput diInitiallyActive(true);
    REQUIRE(diInitiallyActive.isActive());

    REQUIRE(di.getMinRepeatedSamples() == 0);
    REQUIRE_FALSE(di.hasChanged());

    SECTION("without debouncing")
    {
        for (uint16_t i = 0; i < 10; ++i)
        {
            di.setActive(false);
            REQUIRE_FALSE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }

        for (uint16_t i = 0; i < 10; ++i)
        {
            bool odd             = ((i & 1) == 1);
            bool expectedChanged = (di.isActive() != odd);
            di.setActive(odd);
            REQUIRE(di.isActive() == odd);
            REQUIRE(di.hasChanged() == expectedChanged);
        }

        for (uint16_t i = 0; i < 10; ++i)
        {
            di.setActive(true);
            REQUIRE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }
    }

    SECTION("with debouncing")
    {
        constexpr uint16_t MIN_REPEAT = 5;

        di.setMinRepeatedSamples(MIN_REPEAT);

        // initial state
        REQUIRE_FALSE(di.isActive());

        // it was false, so did not repeat yet
        for (uint16_t i = 0; i < MIN_REPEAT; ++i)
        {
            di.setActive(true);
            REQUIRE_FALSE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }

        // now it was repeated MIN_REPEAT times, so it will be set as active value
        di.setActive(true);
        REQUIRE(di.isActive());
        REQUIRE(di.hasChanged());

        // it should keep the same value for some time
        for (uint16_t i = 0; i < MIN_REPEAT * 2; ++i)
        {
            di.setActive(true);
            REQUIRE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }

        // it should keep the same value for while flipping
        bool newValue = false;
        for (uint16_t i = 0; i < MIN_REPEAT * 2; ++i)
        {
            di.setActive(newValue);
            REQUIRE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());

            newValue = !newValue;
        }

        // it sets the DigitalInput to true and then flips the newValue to false
        REQUIRE(newValue == false);

        // lets switch back to false
        // we repeat it MIN_REPEAT - 1 without swithing the output value
        for (uint16_t i = 0; i < MIN_REPEAT; ++i)
        {
            di.setActive(false);
            REQUIRE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }

        di.setActive(false);          // the final repeat...
        REQUIRE_FALSE(di.isActive()); // will switch to a new value
        REQUIRE(di.hasChanged());

        // lets change the min repeated value
        di.setMinRepeatedSamples(0);
        // it will be active immediately
        di.setActive(true);
        REQUIRE(di.isActive());
        REQUIRE(di.hasChanged());

        di.setActive(false);
        REQUIRE_FALSE(di.isActive());
        REQUIRE(di.hasChanged());

        // lets change the min repeated value
        di.setMinRepeatedSamples(MIN_REPEAT);

        for (uint16_t i = 0; i < MIN_REPEAT; ++i)
        {
            di.setActive(true);
            REQUIRE_FALSE(di.isActive());
            REQUIRE_FALSE(di.hasChanged());
        }

        // and now, just before fliping the value we change the repeat count to lower
        di.setMinRepeatedSamples(1);
        REQUIRE_FALSE(di.isActive());
        REQUIRE_FALSE(di.hasChanged());

        di.setActive(false);
        REQUIRE_FALSE(di.isActive());
        REQUIRE_FALSE(di.hasChanged());

        // first appearence of a new value
        di.setActive(true);
        REQUIRE_FALSE(di.isActive());
        REQUIRE_FALSE(di.hasChanged());

        // first repeat
        di.setActive(true);
        REQUIRE(di.isActive());
        REQUIRE(di.hasChanged());
    }
}
