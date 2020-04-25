#include "SingleAxisPropulsionSystemTest.hpp"
#include "ProtobufStructuresComparators.hpp"
#include "PinState.hpp"
#include "CoordinateSystem.hpp"

namespace
{
constexpr auto xCoordinate = 1000;
constexpr auto yCoordinate = 700;
constexpr auto outOfRangeYCoordinate = COORDINATE_SYSTEM::RESOLUTION + 700;
constexpr auto firstEngineFirstInput = 10u;
constexpr auto firstEngineSecondInput = 11u;
constexpr auto firstEnginePwm = 12u;
constexpr auto secondEngineFirstInput = 13u;
constexpr auto secondEngineSecondInput = 14u;
constexpr auto secondEnginePwm = 15u;
constexpr auto pwmValue = 234u;

const PinsConfiguration leftEnginePinsConfiguration {{firstEngineFirstInput,  PIN_STATE::HIGH},
                                                     {firstEngineSecondInput, PIN_STATE::LOW},
                                                     {firstEnginePwm, pwmValue}};

const PinsConfiguration rightEnginePinsConfiguration {{secondEngineFirstInput,  PIN_STATE::HIGH},
                                                     {secondEngineSecondInput, PIN_STATE::LOW},
                                                     {secondEnginePwm, pwmValue}};

auto mergeToPinsConfigurations(const auto firstConfiguration, const auto secondConfiguration)
{
    PinsConfiguration mergedPinsConfiguration;
    mergedPinsConfiguration = firstConfiguration;
    mergedPinsConfiguration.insert(secondConfiguration.begin(), secondConfiguration.end());

    return mergedPinsConfiguration;
}

auto boothEnginesPinsConfiguration = mergeToPinsConfigurations(leftEnginePinsConfiguration, rightEnginePinsConfiguration);

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
    const auto givenCoordinates = createCoordinates(xCoordinate, yCoordinate);

    EXPECT_CALL(_leftEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(leftEnginePinsConfiguration));
    EXPECT_CALL(_rightEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(rightEnginePinsConfiguration));

    EXPECT_CALL(_engineDriverMock, fillPinsConfiguration(givenCoordinates, boothEnginesPinsConfiguration));

    EXPECT_CALL(_leftEngineMock, setPinsConfiguration(boothEnginesPinsConfiguration));
    EXPECT_CALL(_rightEngineMock, setPinsConfiguration(boothEnginesPinsConfiguration));

    ASSERT_NO_THROW(_sut.applyNewConfigurationBasedOnCoordinates(givenCoordinates));
}

TEST_F(SingleAxisPropulsionSystemTest, getPinsConfigurationShouldReturnPinsConfigurationOfBoothEngines)
{
    EXPECT_CALL(_rightEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(rightEnginePinsConfiguration));
    EXPECT_CALL(_leftEngineMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(leftEnginePinsConfiguration));

    ASSERT_EQ(boothEnginesPinsConfiguration, _sut.getPinsConfiguration());
}
