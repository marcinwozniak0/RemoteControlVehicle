#include <gtest/gtest.h>

#include "VehicleTest.hpp"
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
