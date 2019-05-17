#include "SingleAxisPropulsionSystemTest.hpp"

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameValue)
{
    constexpr auto direction = 1u;
    constexpr auto speed = 70;
    constexpr auto pwm = speed * PWM_MAX_RANGE / 100;

    const std::vector<uint8_t> characteristic {direction, speed};
    const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfLeftEngine = {1, 0, pwm};
    const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE> pinValuesOfRightEngine = {0, 1, pwm};
    const std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
            pinValues {pinValuesOfLeftEngine, pinValuesOfRightEngine};

    EXPECT_CALL(_engineDriverMock, calculatePinValues(characteristic)).WillOnce(Return(pinValues));
    EXPECT_CALL(_leftEngineMock, saveValues(pinValuesOfLeftEngine));
    EXPECT_CALL(_rightEngineMock, saveValues(pinValuesOfRightEngine));

    ASSERT_NO_THROW(_sut.transferCharacteristicValues(characteristic));
}
