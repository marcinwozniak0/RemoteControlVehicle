#include "L293DEngineDriverTest.hpp"

namespace
{
constexpr int16_t xCoordinate = 1200;
constexpr int16_t yCoordinateForForwardDirection = 3000;
constexpr int16_t yCoordinateForBackwardDirection = -1000;
constexpr int16_t yCoordinateForStopEngine = 0;
constexpr int16_t overRangeCoordinate = EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION + 15;

const Messages::CoordinateSystem buildCoordinates(int xCoordinate, int yCoordinate)
{
    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    return coordinates;
}

auto createExpectedPinsConfiguration(const int firstEngineFirstOutput, const int firstEngineSecondOutput,
                                     const int secondEngineFirstOutput, const int secondEngineSecondOutput,
                                     const int pwmValue)
{
    PinsConfiguration expectedPinsConfiguration {};

    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  firstEngineFirstOutput);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, firstEngineSecondOutput);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, secondEngineFirstOutput);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,secondEngineSecondOutput);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_PWM,           pwmValue);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_PWM,          pwmValue);

    return expectedPinsConfiguration;
}
}//namespace

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForForwardDirection)
{
    const auto forwardDirectionCharacteristic = buildCoordinates(xCoordinate, yCoordinateForForwardDirection);
    constexpr auto pwmValue = yCoordinateForForwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::HIGH, PIN_STATE::LOW,
                                                                           PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue);

    ASSERT_EQ(_sut.calculatePinsConfiguration(forwardDirectionCharacteristic), expectedPinsConfiguration);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForBackwardDirection)
{
    const auto backwardDirectionCharacteristic = buildCoordinates(xCoordinate, yCoordinateForBackwardDirection);
    constexpr auto pwmValue = yCoordinateForBackwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::LOW, PIN_STATE::HIGH,
                                                                           PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue);

    ASSERT_EQ(_sut.calculatePinsConfiguration(backwardDirectionCharacteristic), expectedPinsConfiguration);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForStopEngine)
{
    const auto stopEngineCharacteristic = buildCoordinates(xCoordinate, yCoordinateForStopEngine);
    constexpr auto pwmValue = yCoordinateForStopEngine * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::HIGH, PIN_STATE::HIGH,
                                                                           PIN_STATE::HIGH, PIN_STATE::HIGH, pwmValue);

    ASSERT_EQ(_sut.calculatePinsConfiguration(stopEngineCharacteristic), expectedPinsConfiguration);
}

struct UnknownCoordinates
{
    UnknownCoordinates(const Messages::CoordinateSystem& coordinateSystem)
        : _coordinateSystem(coordinateSystem)
    {}

    Messages::CoordinateSystem _coordinateSystem;
};

class UnknownCoordinatesTest : public L293DEngineDriverTest,
                               public WithParamInterface<UnknownCoordinates>
{};

TEST_P(UnknownCoordinatesTest, ShouldReturnEmptyPinValues)
{
    PinsConfiguration expectedPinValues {};

    ASSERT_EQ(_sut.calculatePinsConfiguration(GetParam()._coordinateSystem), expectedPinValues);
}

INSTANTIATE_TEST_CASE_P(OverRangeXCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{buildCoordinates(overRangeCoordinate,
                                                                 yCoordinateForBackwardDirection)},
                               UnknownCoordinates{buildCoordinates(-overRangeCoordinate,
                                                                 yCoordinateForBackwardDirection)}));

INSTANTIATE_TEST_CASE_P(OverRangeYCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{buildCoordinates(xCoordinate,
                                                                 overRangeCoordinate)},
                               UnknownCoordinates{buildCoordinates(xCoordinate,
                                                                 -overRangeCoordinate)}));

INSTANTIATE_TEST_CASE_P(OverRangeXAndYCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{buildCoordinates(overRangeCoordinate,
                                                                 overRangeCoordinate)},
                               UnknownCoordinates{buildCoordinates(-overRangeCoordinate,
                                                                 -overRangeCoordinate)}));
