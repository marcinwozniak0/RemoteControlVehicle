#include "CarIdDistributorTest.hpp"

TEST_F(CarIdDistributorTest, firstIdShouldBeEqualZero)
{
    ASSERT_EQ(_sut.getFreeId(), 0);
}

TEST_F(CarIdDistributorTest, nextIdShouldBeGreaterByOneThanPreviousId)
{
    constexpr auto firstId = 0u;
    constexpr auto nextId = firstId + 1;

    _sut.getFreeId();

    ASSERT_EQ(_sut.getFreeId(), nextId);
}
