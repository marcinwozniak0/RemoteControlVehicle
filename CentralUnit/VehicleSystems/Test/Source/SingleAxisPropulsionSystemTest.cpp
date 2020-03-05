#include "SingleAxisPropulsionSystemTest.hpp"
#include "ProtobufStructuresComparators.hpp"
#include "VehicleConfiguration.hpp"

namespace
{
constexpr auto xCoordinate = 1000;
constexpr auto yCoordinate = 700;
constexpr auto outOfRangeYCoordinate = EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION + 700;

auto createCoordinates(const int32_t xCoordinate, const int32_t yCoordinate)
{
    Commands::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    return coordinates;
}
}//namespace

TEST_F(SingleAxisPropulsionSystemTest, eachEngineShouldHasTheSameSpeedValue)
{
    constexpr auto pwmValue = yCoordinate * PWM_MAX_RANGE / EXTERNAL_INTERFACES::COORDINATE_SYSTEM_RESOLUTION;

    const auto givenCoordinates = createCoordinates(xCoordinate, yCoordinate);

    PinsConfiguration expectedPinsConfiguration {};

    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT, PIN_STATE::LOW);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT, PIN_STATE::LOW);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::FIRST_ENGINE_PWM,           pwmValue);
    expectedPinsConfiguration.try_emplace(PIN_NUMBERS::SECOND_ENGINE_PWM,          pwmValue);

    EXPECT_CALL(_engineDriverMock, calculatePinsConfiguration(givenCoordinates)).WillOnce(Return(expectedPinsConfiguration));
    EXPECT_CALL(_leftEngineMock, setPinsConfiguration(expectedPinsConfiguration));
    EXPECT_CALL(_rightEngineMock, setPinsConfiguration(expectedPinsConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates(givenCoordinates));
}


TEST_F(SingleAxisPropulsionSystemTest, EmptyPinsConfigurationShouldNotBeSet)
{
    const PinsConfiguration expectedPinsConfiguration {};
    const auto givenCoordinates = createCoordinates(xCoordinate, yCoordinate);

    EXPECT_CALL(_engineDriverMock, calculatePinsConfiguration(givenCoordinates)).WillOnce(Return(expectedPinsConfiguration));
    EXPECT_CALL(_leftEngineMock, setPinsConfiguration(expectedPinsConfiguration)).Times(0);
    EXPECT_CALL(_rightEngineMock, setPinsConfiguration(expectedPinsConfiguration)).Times(0);

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates(givenCoordinates));
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
