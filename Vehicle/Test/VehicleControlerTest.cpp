#include "VehicleControlerTest.hpp"

namespace Messages {
  struct CoordinateSystem;
  inline bool operator==(const Messages::CoordinateSystem& lhs, const Messages::CoordinateSystem& rhs)
  {
      return lhs.x_coordinate() == rhs.x_coordinate() &&
          lhs.y_coordinate() == rhs.y_coordinate();
  }
}

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

    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    EXPECT_CALL(_propulsionSystemMock, applyNewConfigurationBasedOnCoordinates(coordinates));

    _sut->controlVehicle();

}
