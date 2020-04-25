#include "L293DEngineDriverTest.hpp"

namespace
{
constexpr int16_t xCoordinate = 1200;
constexpr int16_t yCoordinateForForwardDirection = 3000;
constexpr int16_t yCoordinateForBackwardDirection = -1000;
constexpr int16_t yCoordinateForStopEngine = 0;
constexpr int16_t overRangeCoordinate = EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION + 15;
constexpr auto firstEngineFirstInput = 10u;
constexpr auto firstEngineSecondInput = 11u;
constexpr auto firstEnginePwm = 12u;
constexpr auto secondEngineFirstInput = 13u;
constexpr auto secondEngineSecondInput = 14u;
constexpr auto secondEnginePwm = 15u;
constexpr auto pwmValueForStoppedEngines = 0u;
constexpr auto pwmRange = 255u;

const Commands::CoordinateSystem buildCoordinates(int xCoordinate, int yCoordinate)
{
    Commands::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    return coordinates;
}

auto createExpectedPinsConfiguration(const int firstEngineFirstOutput, const int firstEngineSecondOutput,
                                     const int secondEngineFirstOutput, const int secondEngineSecondOutput,
                                     const int pwmValue)
{
    PinsConfiguration expectedPinsConfiguration {};

    expectedPinsConfiguration.try_emplace(firstEngineFirstInput,  firstEngineFirstOutput);
    expectedPinsConfiguration.try_emplace(firstEngineSecondInput, firstEngineSecondOutput);
    expectedPinsConfiguration.try_emplace(firstEnginePwm, pwmValue);
    expectedPinsConfiguration.try_emplace(secondEngineFirstInput, secondEngineFirstOutput);
    expectedPinsConfiguration.try_emplace(secondEngineSecondInput, secondEngineSecondOutput);
    expectedPinsConfiguration.try_emplace(secondEnginePwm, pwmValue);

    return expectedPinsConfiguration;
}

auto createEmptyPinsConfiguration()
{
    return createExpectedPinsConfiguration(0, 0, 0, 0, 0);
}
}//namespace

L293DEngineDriverTest::L293DEngineDriverTest()
    : _sut(pwmRange)
{}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForForwardDirection)
{
    const auto forwardDirectionCharacteristic = buildCoordinates(xCoordinate, yCoordinateForForwardDirection);
    constexpr auto pwmValue = yCoordinateForForwardDirection * pwmRange / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::HIGH, PIN_STATE::LOW,
                                                                           PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue);
    auto pinsConfigurationToFill = createEmptyPinsConfiguration();

    _sut.fillPinsConfiguration(forwardDirectionCharacteristic, pinsConfigurationToFill);

    ASSERT_EQ(pinsConfigurationToFill, expectedPinsConfiguration);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForBackwardDirection)
{
    const auto backwardDirectionCharacteristic = buildCoordinates(xCoordinate, yCoordinateForBackwardDirection);
    constexpr auto pwmValue = std::abs(yCoordinateForBackwardDirection) * pwmRange / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::LOW, PIN_STATE::HIGH,
                                                                           PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue);

    auto pinsConfigurationToFill = createEmptyPinsConfiguration();

    _sut.fillPinsConfiguration(backwardDirectionCharacteristic, pinsConfigurationToFill);

    ASSERT_EQ(pinsConfigurationToFill, expectedPinsConfiguration);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForStopEngine)
{
    const auto stopEngineCharacteristic = buildCoordinates(xCoordinate, yCoordinateForStopEngine);

    const auto expectedPinsConfiguration = createExpectedPinsConfiguration(PIN_STATE::HIGH, PIN_STATE::HIGH,
                                                                           PIN_STATE::HIGH, PIN_STATE::HIGH, pwmValueForStoppedEngines);

    auto pinsConfigurationToFill = createEmptyPinsConfiguration();

    _sut.fillPinsConfiguration(stopEngineCharacteristic, pinsConfigurationToFill);

    ASSERT_EQ(pinsConfigurationToFill, expectedPinsConfiguration);
}

struct UnknownCoordinates
{
    UnknownCoordinates(const Commands::CoordinateSystem& coordinateSystem)
        : _coordinateSystem(coordinateSystem)
    {}

    Commands::CoordinateSystem _coordinateSystem;
};

class UnknownCoordinatesTest : public L293DEngineDriverTest,
                               public WithParamInterface<UnknownCoordinates>
{};

TEST_P(UnknownCoordinatesTest, ShouldReturnPinValuesForStopEngines)
{
    PinsConfiguration expectedPinValues = createExpectedPinsConfiguration(PIN_STATE::HIGH, PIN_STATE::HIGH,
                                                                          PIN_STATE::HIGH, PIN_STATE::HIGH, pwmValueForStoppedEngines);

    auto pinsConfigurationToFill = createEmptyPinsConfiguration();

    _sut.fillPinsConfiguration(GetParam()._coordinateSystem, pinsConfigurationToFill);

    ASSERT_EQ(pinsConfigurationToFill, expectedPinValues);
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
