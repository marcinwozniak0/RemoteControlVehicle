#include "FrontAxialSteeringSystemTest.hpp"

namespace
{
static constexpr auto STEERING_WHEEL_PWM_DUTY_CYCLE_IN_NEUTRAL_POSITION = 0.075;
static constexpr auto STEERING_WHEEL_PWM_DUTY_CYCLE_IN_30_DEGREES_POSITION = 0.166;
static constexpr auto STEERING_WHEEL_PWM_VALUE_IN_NEUTRAL_POSITION =
        static_cast<int>(255 * STEERING_WHEEL_PWM_DUTY_CYCLE_IN_NEUTRAL_POSITION);
static constexpr auto STEERING_WHEEL_PWM_VALUE_IN_30_DEGREES_POSITION =
        static_cast<int>(255 * STEERING_WHEEL_PWM_DUTY_CYCLE_IN_30_DEGREES_POSITION);
}
TEST_F(FrontAxialSteeringSystemTest, GetPinsConfigurationShouldCallSameMethodFromSteeringWheel)
{
    PinsConfiguration pinsConfiguration {};
    EXPECT_CALL(_steeringWheelMock, getPinsConfiguration()).WillOnce(ReturnRef(pinsConfiguration));

    ASSERT_NO_THROW(_sut.getPinsConfiguration());
}

TEST_F(FrontAxialSteeringSystemTest, WhenReceivedCoordinatesAreZeroPwmValueShouldBeNeutral)
{
    const PinsConfiguration expectedConfiguration{std::make_pair(PIN_NUMBERS::STEERING_WHEEL_PWM,
                                                                 STEERING_WHEEL_PWM_VALUE_IN_NEUTRAL_POSITION)};

    EXPECT_CALL(_steeringWheelMock, setPinsConfiguration(expectedConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates({0, 0}));
}

TEST_F(FrontAxialSteeringSystemTest, WhenReceivedCoordinatesHaveMaximumPositiveValuesPwmValueShouldBeHavleValueFor30DegreeSAngle)
{
    const PinsConfiguration expectedConfiguration{std::make_pair(PIN_NUMBERS::STEERING_WHEEL_PWM,
                                                                 STEERING_WHEEL_PWM_VALUE_IN_30_DEGREES_POSITION)};

    EXPECT_CALL(_steeringWheelMock, setPinsConfiguration(expectedConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates({EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION,
                                                                  EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION}));
}
