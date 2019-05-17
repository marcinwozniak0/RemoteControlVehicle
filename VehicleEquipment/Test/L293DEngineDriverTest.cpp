#include "L293DEngineDriverTest.hpp"

namespace
{
constexpr uint8_t speedValue = 70;
constexpr uint8_t pwmValue = 70 * PWM_MAX_RANGE / 100;
}//namespace

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForForwardDirectionMarker)
{
    constexpr auto forwardDirectionMarker = 1u;
    const std::vector<uint8_t> characteristic {forwardDirectionMarker, speedValue};
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::HIGH, PIN_STATE::LOW , pwmValue},
                                {PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinValues(characteristic), expectedPinValues);
}

TEST_F(L293DEngineDriverTest, shouldReturnPinValuesForBackwardDirectionMarker)
{
    constexpr auto backwardDirectionMarker = 0u;
    const std::vector<uint8_t> characteristic {backwardDirectionMarker, speedValue};
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue},
                                {PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue}}};

    ASSERT_EQ(_sut.calculatePinValues(characteristic), expectedPinValues);
}

TEST_F(L293DEngineDriverTest, shouldReturnEmptyPinValuesForUnknowDirectionMarker)
{
    constexpr auto unknownDirectionMarker = 26u;
    const std::vector<uint8_t> characteristic {unknownDirectionMarker, speedValue};
    std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            expectedPinValues {{{},{}}};

    ASSERT_EQ(_sut.calculatePinValues(characteristic), expectedPinValues);
}
