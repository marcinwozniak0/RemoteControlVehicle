#include "VehicleControlerTest.hpp"

TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    COMMANDS_QUEUE->push("START");
    COMMANDS_QUEUE->push("DEACTIVATE");

    _sut->controlVehicle();

    EXPECT_EQ(VehicleState::Manual, _vehicle.getVehicleState());
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    COMMANDS_QUEUE->push("STOP");
    COMMANDS_QUEUE->push("DEACTIVATE");

    _sut->controlVehicle();

    EXPECT_EQ(VehicleState::Idle, _vehicle.getVehicleState());
}
