#include "SingleAxisPropulsionSystemTest.hpp"

namespace Messages {
  struct CoordinateSystem;
  inline bool operator==(const Messages::CoordinateSystem& lhs, const Messages::CoordinateSystem& rhs)
  {
      return lhs.x_coordinate() == rhs.x_coordinate() &&
          lhs.y_coordinate() == rhs.y_coordinate();
  }
}

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameSpeedValue)
{
    constexpr auto xCoordinate = 1000;
    constexpr auto yCoordinate = 700;
    constexpr auto pwmValue = yCoordinate * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;


    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    PinsConfiguration expectedPinsConfiguration {};

    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, PIN_STATE::LOW);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, PIN_STATE::LOW);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_PWM,           pwmValue);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_PWM,          pwmValue);

    EXPECT_CALL(_engineDriverMock, calculatePinsConfiguration(coordinates)).WillOnce(Return(expectedPinsConfiguration));
    EXPECT_CALL(_leftEngineMock, setPinsConfiguration(expectedPinsConfiguration));
    EXPECT_CALL(_rightEngineMock, setPinsConfiguration(expectedPinsConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates(coordinates));
}

TEST_F(SingleAxisPropulsionSystemTest, getPinsConfigurationShouldReturnPinsConfigurationOfBoothEngines)
{
    const PinsConfiguration boothEnginesPinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH},
                                                             {PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH},
                                                             {PIN_NUMBERS::SECOND_ENGINE_PWM,          0}};

    const PinsConfiguration rightEnginePinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH}};

    const PinsConfiguration leftEnginePinsConfiguration = {{PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH},
                                                           {PIN_NUMBERS::SECOND_ENGINE_PWM,          0}};

    EXPECT_CALL(_rightEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(rightEnginePinsConfiguration));
    EXPECT_CALL(_leftEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(leftEnginePinsConfiguration));

    ASSERT_EQ(boothEnginesPinsConfiguration, _sut.getPinsConfiguration());
}
