#include "catch.hpp"

#include "CircularBuffer.hpp"

TEST_CASE("CircularBuffer")
{
    constexpr uint16_t SIZE = 2;

    // common
    using CB = ET::CircularBuffer<SIZE, uint16_t>;

    CB            cb;
    CB::valueType v;
    REQUIRE(cb.getCapacity() == SIZE);
    REQUIRE(cb.getSize() == 0);

    SECTION("adding 1 value")
    {
        cb.push(1);
        REQUIRE(cb.getSize() == 1);

        REQUIRE(cb.pop(v));
        REQUIRE(v == 1);
        REQUIRE(cb.getSize() == 0);

        REQUIRE_FALSE(cb.pop(v));
        REQUIRE(cb.getSize() == 0);

        cb.push(2);
        REQUIRE(cb.getSize() == 1);
        REQUIRE(cb.pop(v));
        REQUIRE(v == 2);
        REQUIRE(cb.getSize() == 0);

        cb.push(3);
        REQUIRE(cb.getSize() == 1);
        REQUIRE(cb.pop(v));
        REQUIRE(v == 3);
        REQUIRE(cb.getSize() == 0);

        cb.push(4);
        REQUIRE(cb.getSize() == 1);
        REQUIRE(cb.pop(v));
        REQUIRE(v == 4);
        REQUIRE(cb.getSize() == 0);
    }

    SECTION("adding till max capacity")
    {
        cb.push(1);
        REQUIRE(cb.getSize() == 1);

        cb.push(2);
        REQUIRE(cb.getSize() == 2);

        REQUIRE(cb.pop(v));
        REQUIRE(v == 1);
        REQUIRE(cb.getSize() == 1);

        REQUIRE(cb.pop(v));
        REQUIRE(v == 2);
        REQUIRE(cb.getSize() == 0);

        REQUIRE_FALSE(cb.pop(v));
        REQUIRE(cb.getSize() == 0);
    }

    SECTION("adding beyond max capacity")
    {
        cb.push(1); // 1
        REQUIRE(cb.getSize() == 1);

        cb.push(2); // 1 2
        REQUIRE(cb.getSize() == SIZE);

        cb.push(3); // 2 3
        REQUIRE(cb.getSize() == SIZE);

        REQUIRE(cb.pop(v)); // 3
        REQUIRE(v == 2);
        REQUIRE(cb.getSize() == 1);

        REQUIRE(cb.pop(v));
        REQUIRE(v == 3);
        REQUIRE(cb.getSize() == 0);

        cb.push(4); // 4
        REQUIRE(cb.getSize() == 1);

        cb.push(5); // 4 5
        REQUIRE(cb.getSize() == SIZE);

        cb.push(6); // 5 6
        REQUIRE(cb.getSize() == SIZE);

        REQUIRE(cb.pop(v)); // 6
        REQUIRE(v == 5);
        REQUIRE(cb.getSize() == 1);

        cb.push(7); // 6 7
        REQUIRE(cb.getSize() == SIZE);

        REQUIRE(cb.pop(v)); // 7
        REQUIRE(v == 6);
        REQUIRE(cb.getSize() == 1);

        REQUIRE(cb.pop(v));
        REQUIRE(v == 7);
        REQUIRE(cb.getSize() == 0);

        REQUIRE_FALSE(cb.pop(v));
    }
}
