#include "ThirtyDegreesSteeringWheelTest.hpp"

TEST_F(ThirtyDegreesSteeringWheelTest, PinValueShouldBeSetToZeroAtBegin)
{
    constexpr uint8_t expectedPinValue = 0;
    const PinConfiguration expectedConfiguration{std::make_pair(steeringWheelPwmPinNumer, expectedPinValue)};

    ASSERT_EQ(expectedConfiguration, _sut.getConfiguration());
}
