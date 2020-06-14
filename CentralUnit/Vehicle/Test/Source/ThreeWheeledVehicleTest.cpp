#include <gtest/gtest.h>

#include "ThreeWheeledVehicleTest.hpp"
#include "VehicleState.hpp"
#include "PinState.hpp"

namespace
{
constexpr auto firstPinNumber = 23u;
constexpr auto secondPinNumber = 11u;
constexpr auto thirdPinNumber = 2u;
}

TEST_F(ThreeWheeledVehicleTest, vehicleStateShouldBeIdleByDefault)
{
    EXPECT_EQ(VehicleState::Idle, _sut.getVehicleState());
}

TEST_F(ThreeWheeledVehicleTest, vehicleStateShouldBeManualAfterVehicleStart)
{
    _sut.startVehicle();
    EXPECT_EQ(VehicleState::Manual, _sut.getVehicleState());
}

TEST_F(ThreeWheeledVehicleTest, vehicleStateShouldBeAutoAfterSwitchToAutomaticMode)
{
    _sut.switchToAutomaticMode();
    EXPECT_EQ(VehicleState::Auto, _sut.getVehicleState());
}

TEST_F(ThreeWheeledVehicleTest, vehicleStateShouldBeIdleAfterVehicleStop)
{
    _sut.stopVehicle();
    EXPECT_EQ(VehicleState::Idle, _sut.getVehicleState());
}

TEST_F(ThreeWheeledVehicleTest, getCurrentPinsConfigurationShouldReturnPinsConfigurationOfAllVehicleSystems)
{
    const PinsConfiguration vehiclePinsConfiguration = {{firstPinNumber, PIN_STATE::HIGH},
                                                        {secondPinNumber,PIN_STATE::HIGH},
                                                        {thirdPinNumber, 0}};

    const PinsConfiguration propulsionSystemPinsConfiguration = {{firstPinNumber,  PIN_STATE::HIGH}};

    const PinsConfiguration steeringSystemPinsConfiguration = {{secondPinNumber,PIN_STATE::HIGH},
                                                               {thirdPinNumber, 0}};

    EXPECT_CALL(*_steeringSystemMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(propulsionSystemPinsConfiguration));
    EXPECT_CALL(*_propulsionSystemMock, getPinsConfiguration()).WillRepeatedly(Return(steeringSystemPinsConfiguration));

    EXPECT_EQ(vehiclePinsConfiguration, _sut.getCurrentPinsConfiguration());
}
