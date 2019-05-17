#include "SingleAxisPropulsionSystemTest.hpp"

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameSpeedValue)
{
    constexpr auto direction = 1u;
    constexpr auto speed = 70;
    constexpr auto pwmValue = speed * PWM_MAX_RANGE / 100;

    const std::vector<uint8_t> characteristic {direction, speed};
    const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine =
        {PIN_STATE::HIGH, PIN_STATE::LOW, pwmValue};
    const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine =
        {PIN_STATE::LOW, PIN_STATE::HIGH, pwmValue};
    const std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            pinValues {pinValuesOfLeftEngine, pinValuesOfRightEngine};

    EXPECT_CALL(_engineDriverMock, calculatePinValues(characteristic)).WillOnce(Return(pinValues));
    EXPECT_CALL(_leftEngineMock, saveValues(pinValuesOfLeftEngine));
    EXPECT_CALL(_rightEngineMock, saveValues(pinValuesOfRightEngine));

    ASSERT_NO_THROW(_sut.transferCharacteristicValues(characteristic));
}
