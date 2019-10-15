#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>

#include "VehicleControlerTest.hpp"

namespace
{
constexpr int32_t xCoordinate = 700;
constexpr int32_t yCoordinate = 5500;

const std::string createSerializedDeactivateMessage()
{
    Messages::Deactivate deactivateMessage;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(deactivateMessage);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToStart()
{
    Messages::UserCommandToStart userCommandToStart;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(userCommandToStart);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToStop()
{
    Messages::UserCommandToStop userCommandToStop;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    topLevelMessage.PackFrom(userCommandToStop);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}

const std::string createSerializedUserCommandToRun()
{
    Messages::UserCommandToRun userCommandToRun;
    google::protobuf::Any topLevelMessage;
    std::string serializedMessage;

    userCommandToRun.mutable_coordinate_system()->set_x_coordinate(xCoordinate);
    userCommandToRun.mutable_coordinate_system()->set_y_coordinate(yCoordinate);

    topLevelMessage.PackFrom(userCommandToRun);
    topLevelMessage.SerializeToString(&serializedMessage);

    return serializedMessage;
}
}//namespace

namespace Messages
{
  struct CoordinateSystem;
  inline bool operator==(const Messages::CoordinateSystem& lhs, const Messages::CoordinateSystem& rhs)
  {
      return lhs.x_coordinate() == rhs.x_coordinate() &&
          lhs.y_coordinate() == rhs.y_coordinate();
  }
}


TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    EXPECT_CALL(_vehicleMock, startVehicle());
    EXPECT_CALL(_messageReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    EXPECT_CALL(_vehicleMock, stopVehicle());
    EXPECT_CALL(_messageReceiverMock, takeMessageFromQueue()).Times(3)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedUserCommandToStop()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, afterReceiveDriveCommandShouldApplyNewVehicleConfiguration)
{
    EXPECT_CALL(_messageReceiverMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToRun()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    EXPECT_CALL(_vehicleMock, applyNewConfiguration(coordinates));

    _sut.controlVehicle();

}
