#include <UserCommandToRun.pb.h>

#include "FrontAxialSteeringSystemTest.hpp"
#include "CoordinateSystem.hpp"

namespace
{
static constexpr auto steeringWheelPwmDutyCycleInNeutralPosition = 0.075;
static constexpr auto steeringWheelPwmDutyCycleIn30DegreesPosition = steeringWheelPwmDutyCycleInNeutralPosition + 0.0166;
static constexpr auto steeringWheelPwmDutyCycleInMinus30DegreesPosition = steeringWheelPwmDutyCycleInNeutralPosition - 0.0166;
static constexpr auto pwmMaxRange = 255;
static constexpr auto pwmPinNumber = 13u;
static constexpr auto coordinateSystemResolution = COORDINATE_SYSTEM::RESOLUTION;
static constexpr int steeringWheelPwmValueInNeutralPosition = pwmMaxRange * steeringWheelPwmDutyCycleInNeutralPosition;
static constexpr int steeringWheelPwmValueIn30DegreesPosition = pwmMaxRange * steeringWheelPwmDutyCycleIn30DegreesPosition;
static constexpr int steeringWheelPwmValueInMinus30DegreesPosition = pwmMaxRange * steeringWheelPwmDutyCycleInMinus30DegreesPosition;
const PinsConfiguration steeringWheelPinsConfiguration = {{pwmPinNumber, 5648}};

auto buildCoordinates(int x, int y)
{
    Commands::CoordinateSystem coordinateSystem;
    coordinateSystem.set_x_coordinate(x);
    coordinateSystem.set_y_coordinate(y);

    return coordinateSystem;
}
}

TEST_F(FrontAxialSteeringSystemTest, GetPinsConfigurationShouldCallSameMethodFromSteeringWheel)
{
    PinsConfiguration pinsConfiguration {};
    EXPECT_CALL(*_steeringWheelMock, getPinsConfiguration()).WillOnce(ReturnRef(pinsConfiguration));

    ASSERT_NO_THROW(_sut.getPinsConfiguration());
}

#pragma GCC diagnostic ignored "-Wclass-memaccess"
struct PwmValueTest
{
    PwmValueTest(PinsConfiguration x, Commands::CoordinateSystem y)
        : expectedConfiguration(x)
        , givenCoordinates(y)
    {}

    PinsConfiguration expectedConfiguration;
    Commands::CoordinateSystem givenCoordinates;

    PwmValueTest(const PwmValueTest& a)
    {
        memset(this, 0, sizeof(*this));
        this->expectedConfiguration = a.expectedConfiguration;
        this->givenCoordinates = a.givenCoordinates;
    }
};
#pragma GCC diagnostic pop

struct CalculatePwmValueTest : FrontAxialSteeringSystemTest,
                               ::WithParamInterface<PwmValueTest>
{};

TEST_P(CalculatePwmValueTest, fromGivenCoordinatesShouldApplyPwmValue)
{
    EXPECT_CALL(*_steeringWheelMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(steeringWheelPinsConfiguration));
    EXPECT_CALL(*_steeringWheelMock, setPinsConfiguration(GetParam().expectedConfiguration));

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
