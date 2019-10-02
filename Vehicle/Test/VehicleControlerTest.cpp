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

    EXPECT_CALL(_vehicleMock, startVehicle());

    _sut->controlVehicle();
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    _commandQueue->push(createSerializedUserCommandToStart());
    _commandQueue->push(createSerializedUserCommandToStop());
    _commandQueue->push(createSerializedDeactivateMessage());

    EXPECT_CALL(_vehicleMock, stopVehicle());

    _sut->controlVehicle();
}

TEST_F(VehicleControlerTest, afterReceiveDriveCommandShouldApplyNewVehicleConfiguration)
{
    _commandQueue->push(createSerializedUserCommandToRun());
    _commandQueue->push(createSerializedDeactivateMessage());

    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    EXPECT_CALL(_vehicleMock, applyNewConfiguration(coordinates));

    _sut->controlVehicle();

}
