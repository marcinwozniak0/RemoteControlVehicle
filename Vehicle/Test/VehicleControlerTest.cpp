#include "VehicleControlerTest.hpp"

TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    _commandQueue->push(createSerializedUserCommandToStart());
    _commandQueue->push(createSerializedDeactivateMessage());

    _sut->controlVehicle();

    EXPECT_EQ(VehicleState::Manual, _vehicle.getVehicleState());
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    _commandQueue->push(createSerializedUserCommandToStart());
    _commandQueue->push(createSerializedUserCommandToStop());
    _commandQueue->push(createSerializedDeactivateMessage());

    _sut->controlVehicle();

    EXPECT_EQ(VehicleState::Idle, _vehicle.getVehicleState());
}

TEST_F(VehicleControlerTest, afterReceiveDriveCommandShouldTransferToEngineProperValues)
{
    _commandQueue->push(createSerializedUserCommandToRun());
    _commandQueue->push(createSerializedDeactivateMessage());

    EXPECT_CALL(_propulsionSystemMock, applyNewConfigurationBasedOnCoordinates(std::make_pair(xCoordinate, yCoordinate)));

    _sut->controlVehicle();

}
