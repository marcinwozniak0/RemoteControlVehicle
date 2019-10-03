#include "FrontAxialSteeringSystemTest.hpp"

#include <UserCommandToRun.pb.h>

namespace
{
static constexpr auto steeringWheelPwmDutyCycleInNeutralPosition = 0.075;
static constexpr auto steeringWheelPwmDutyCycleIn30DegreesPosition = steeringWheelPwmDutyCycleInNeutralPosition + 0.0166;
static constexpr auto steeringWheelPwmDutyCycleInMinus30DegreesPosition = steeringWheelPwmDutyCycleInNeutralPosition - 0.0166;
static constexpr auto pwmMaxRange = 255;
static constexpr auto pwmPinNumber = PIN_NUMBERS::STEERING_WHEEL_PWM;
static constexpr auto coordinateSystemResolution = EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;
static constexpr int steeringWheelPwmValueInNeutralPosition = pwmMaxRange * steeringWheelPwmDutyCycleInNeutralPosition;
static constexpr int steeringWheelPwmValueIn30DegreesPosition = pwmMaxRange * steeringWheelPwmDutyCycleIn30DegreesPosition;
static constexpr int steeringWheelPwmValueInMinus30DegreesPosition = pwmMaxRange * steeringWheelPwmDutyCycleInMinus30DegreesPosition;

auto buildCoordinates(int x, int y)
{
    Messages::CoordinateSystem coordinateSystem;
    coordinateSystem.set_x_coordinate(x);
    coordinateSystem.set_y_coordinate(y);

    return coordinateSystem;
}
}

TEST_F(FrontAxialSteeringSystemTest, GetPinsConfigurationShouldCallSameMethodFromSteeringWheel)
{
    PinsConfiguration pinsConfiguration {};
    EXPECT_CALL(_steeringWheelMock, getPinsConfiguration()).WillOnce(ReturnRef(pinsConfiguration));

    ASSERT_NO_THROW(_sut.getPinsConfiguration());
}

struct PwmValueTest
{
    PwmValueTest(PinsConfiguration x, Messages::CoordinateSystem y)
        : expectedConfiguration(x)
        , givenCoordinates(y)
    {}

    const PinsConfiguration expectedConfiguration;
    const Messages::CoordinateSystem givenCoordinates;
};

struct CalculatePwmValueTest : FrontAxialSteeringSystemTest,
                               ::WithParamInterface<PwmValueTest>
{};

TEST_P(CalculatePwmValueTest, FromGivenCoordinatesShouldApplyPwmValue)
{
    EXPECT_CALL(_steeringWheelMock, setPinsConfiguration(GetParam().expectedConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates(GetParam().givenCoordinates));
}

INSTANTIATE_TEST_CASE_P(WhenSteeringAngleExceeds30Degree, CalculatePwmValueTest,
                        Values(PwmValueTest{PinsConfiguration{{pwmPinNumber, steeringWheelPwmValueInMinus30DegreesPosition}},
                               buildCoordinates(coordinateSystemResolution, coordinateSystemResolution)}
                              ,PwmValueTest{PinsConfiguration{{pwmPinNumber, steeringWheelPwmValueInMinus30DegreesPosition}},
                               buildCoordinates(coordinateSystemResolution, -coordinateSystemResolution)}
                              ,PwmValueTest{PinsConfiguration{{pwmPinNumber, steeringWheelPwmValueIn30DegreesPosition}},
                               buildCoordinates(-coordinateSystemResolution, coordinateSystemResolution)}
                              ,PwmValueTest{PinsConfiguration{{pwmPinNumber, steeringWheelPwmValueIn30DegreesPosition}},
                               buildCoordinates(-coordinateSystemResolution, -coordinateSystemResolution)}));

INSTANTIATE_TEST_CASE_P(WhenSteeringAngleNotExceeds30Degree, CalculatePwmValueTest,
                        Values(PwmValueTest{PinsConfiguration{{pwmPinNumber, steeringWheelPwmValueInNeutralPosition}},
                               buildCoordinates(0, 0)}));
