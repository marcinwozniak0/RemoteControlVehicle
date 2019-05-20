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

TEST_F(VehicleControlerTest, afterReceiveDriveCommandShouldTransferToEngineProperValues)
{
    COMMANDS_QUEUE->push("DRIVE|700|5500|");
    COMMANDS_QUEUE->push("DEACTIVATE");

    constexpr int16_t xCoordinate = 700;
    constexpr int16_t yCoordinate = 5500;

    EXPECT_CALL(_propulsionSystemMock, transferCharacteristicValues(std::make_pair(xCoordinate, yCoordinate)));

    _sut->controlVehicle();

}
