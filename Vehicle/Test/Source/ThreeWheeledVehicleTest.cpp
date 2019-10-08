#include <gtest/gtest.h>

#include "ThreeWheeledVehicleTest.hpp"
#include "VehicleState.hpp"

TEST_F(VehicleTest, vehicleStateShouldBeIdleByDefault)
{
    EXPECT_EQ(VehicleState::Idle, _sut.getVehicleState());
}

TEST_F(VehicleTest, vehicleStateShouldBeManualAfterVehicleStart)
{
    _sut.startVehicle();
    EXPECT_EQ(VehicleState::Manual, _sut.getVehicleState());
}

TEST_F(VehicleTest, vehicleStateShouldBeAutoAfterSwitchToAutomaticMode)
{
    _sut.switchToAutomaticMode();
    EXPECT_EQ(VehicleState::Auto, _sut.getVehicleState());
}

TEST_F(VehicleTest, vehicleStateShouldBeIdleAfterVehicleStop)
{
    _sut.stopVehicle();
    EXPECT_EQ(VehicleState::Idle, _sut.getVehicleState());
}

TEST_F(VehicleTest, getCurrentPinsConfigurationShouldReturnPinsConfigurationOfAllVehicleSystems)
{
    const PinsConfiguration vehiclePinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH},
                                                        {PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH},
                                                        {PIN_NUMBERS::SECOND_ENGINE_PWM,          0}};

    const PinsConfiguration propulsionSystemPinsConfiguration = {{PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,  PIN_STATE::HIGH}};

    const PinsConfiguration steeringSystemPinsConfiguration = {{PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,PIN_STATE::HIGH},
                                                               {PIN_NUMBERS::SECOND_ENGINE_PWM,          0}};

    EXPECT_CALL(_steeringSystemMock, getPinsConfiguration()).WillRepeatedly(ReturnRef(propulsionSystemPinsConfiguration));
    EXPECT_CALL(_propulsionSystemMock, getPinsConfiguration()).WillRepeatedly(Return(steeringSystemPinsConfiguration));

    EXPECT_EQ(vehiclePinsConfiguration, _sut.getCurrentPinsConfiguration());
}
