#include "L293DEngineDriverTest.hpp"

namespace
{
constexpr int16_t xCoordinate = 1200;
constexpr int16_t yCoordinateForForwardDirection = 3000;
constexpr int16_t yCoordinateForBackwardDirection = -1000;
constexpr int16_t yCoordinateForStopEngine = 0;
constexpr int16_t overRangeCoordinete = EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION + 15;
}//namespace

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForForwardDirection)
{
    constexpr auto forwardDirectionCharacteristic = std::make_pair(xCoordinate, yCoordinateForForwardDirection);
    constexpr uint8_t pwmValue = yCoordinateForForwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::HIGH, PIN_STATE::LOW , pwmValue},
                                {PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinsConfiguration(forwardDirectionCharacteristic), expectedPinValues);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForBackwardDirection)
{
    constexpr auto backwardDirectionCharacteristic = std::make_pair(xCoordinate, yCoordinateForBackwardDirection);
    constexpr uint8_t pwmValue = yCoordinateForBackwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue},
                                {PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinsConfiguration(backwardDirectionCharacteristic), expectedPinValues);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForStopEngine)
{
    constexpr auto stopEngineCharacteristic = std::make_pair(xCoordinate, yCoordinateForStopEngine);
    constexpr uint8_t pwmValue = yCoordinateForStopEngine * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::HIGH, PIN_STATE::HIGH, pwmValue},
                                {PIN_STATE::HIGH, PIN_STATE::HIGH, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinsConfiguration(stopEngineCharacteristic), expectedPinValues);
}

struct UnknownCoordinates
{
    std::pair<int32_t, int32_t> coordinateSystem;
};

class UnknownCoordinatesTest : public L293DEngineDriverTest,
                               public WithParamInterface<UnknownCoordinates>
{};

TEST_P(UnknownCoordinatesTest, ShouldReturnEmptyPinValues)
{
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{},{}}};

    ASSERT_EQ(_sut.calculatePinsConfiguration(GetParam().coordinateSystem), expectedPinValues);
}

INSTANTIATE_TEST_CASE_P(OverRangeXCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{std::make_pair(overRangeCoordinete,
                                                                 yCoordinateForBackwardDirection)},
                               UnknownCoordinates{std::make_pair(-overRangeCoordinete,
                                                                 yCoordinateForBackwardDirection)}));

INSTANTIATE_TEST_CASE_P(OverRangeYCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{std::make_pair(xCoordinate,
                                                                 overRangeCoordinete)},
                               UnknownCoordinates{std::make_pair(xCoordinate,
                                                                 -overRangeCoordinete)}));

INSTANTIATE_TEST_CASE_P(OverRangeXAndYCoordinate, UnknownCoordinatesTest,
                        Values(UnknownCoordinates{std::make_pair(overRangeCoordinete,
                                                                 overRangeCoordinete)},
                               UnknownCoordinates{std::make_pair(-overRangeCoordinete,
                                                                 -overRangeCoordinete)}));
