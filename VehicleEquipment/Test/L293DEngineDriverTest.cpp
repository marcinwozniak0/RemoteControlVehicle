#include "L293DEngineDriverTest.hpp"

namespace
{
constexpr int16_t xCoordinate = 1200;
constexpr int16_t yCoordinateForForwardDirection = 3000;
constexpr int16_t yCoordinateForBackwardDirection = -1000;
}//namespace

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForForwardDirectionMarker)
{
    constexpr auto forwardDirectionCharacteristic = std::make_pair(xCoordinate, yCoordinateForForwardDirection);
    constexpr uint8_t pwmValue = yCoordinateForForwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::HIGH, PIN_STATE::LOW , pwmValue},
                                {PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinValues(forwardDirectionCharacteristic), expectedPinValues);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForBackwardDirectionMarker)
{
    constexpr auto backwardDirectionCharacteristic = std::make_pair(xCoordinate, yCoordinateForBackwardDirection);
    constexpr uint8_t pwmValue = yCoordinateForBackwardDirection * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue},
                                {PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinValues(backwardDirectionCharacteristic), expectedPinValues);
}

/*TEST_F(L293DEngineDriverTest, shouldReturnEmptyPinValuesForUnknowDirectionMarker)
{
    constexpr auto unknownDirectionMarker = 26u;
    const std::vector<uint8_t> characteristic {unknownDirectionMarker, speedValue};
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{},{}}};

    ASSERT_EQ(_sut.calculatePinValues(characteristic), expectedPinValues);
}*/
