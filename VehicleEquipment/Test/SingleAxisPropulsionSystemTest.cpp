#include "SingleAxisPropulsionSystemTest.hpp"

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameSpeedValue)
{
    constexpr int16_t xCoordinate = 1000;
    constexpr int16_t yCoordinate = 700;
    constexpr auto pwmValue = yCoordinate * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto characteristic = std::make_pair(xCoordinate, yCoordinate);
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
