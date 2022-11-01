#include "catch2/catch_test_macros.hpp"

#include "et/MovingAverage.hpp"

TEST_CASE("MovingAverage")
{
    constexpr uint16_t SIZE = 3;

    // common
    using MA = ET::MovingAverage<SIZE, uint16_t>;

    MA::valueType v;
    MA            ma;
    REQUIRE(ma.getCapacity() == SIZE);
    REQUIRE(ma.getSize() == 0);
    REQUIRE(ma.getSum() == 0);
    REQUIRE(ma.getAverage() == 0);

    SECTION("simple test")
    {
        ma.push(1);
        REQUIRE(ma.getSize() == 1);
        REQUIRE(ma.getSum() == 1);
        REQUIRE(ma.getAverage() == 1);

        REQUIRE(ma.pop(v));
        REQUIRE(v == 1);
        REQUIRE(ma.getSize() == 0);
        REQUIRE(ma.getSum() == 0);
        REQUIRE(ma.getAverage() == 0);

        REQUIRE_FALSE(ma.pop(v));

        ma.push(2);
        REQUIRE(ma.getSize() == 1);
        ma.push(4);
        REQUIRE(ma.getSize() == 2);
        REQUIRE(ma.getSum() == 6);
        REQUIRE(ma.getAverage() == 6 / 2);

        ma.push(3);
        REQUIRE(ma.getSize() == 3);
        REQUIRE(ma.getSum() == 2 + 4 + 3);
        REQUIRE(ma.getAverage() == 9 / 3);

        ma.push(5);
        REQUIRE(ma.getSize() == 3);
        REQUIRE(ma.getSum() == 4 + 3 + 5);
        REQUIRE(ma.getAverage() == 12 / 3);


    }
}
