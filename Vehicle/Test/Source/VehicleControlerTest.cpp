#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>

#include "VehicleControlerTest.hpp"
#include "ControlerCommandToRunMessageBuilder.hpp"

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

namespace google::protobuf
{
inline bool operator==(const google::protobuf::Map<int, int>& lhs, const google::protobuf::Map<int, int>& rhs)
{

    return lhs.size() == rhs.size() &&
           std::is_permutation(lhs.begin(),
                               lhs.end(),
                               rhs.begin(),
                               [](const auto a, const auto b){return a.first == b.first;});
}
}

namespace Messages
{
  struct CoordinateSystem;
  inline bool operator==(const Messages::CoordinateSystem& lhs, const Messages::CoordinateSystem& rhs)
  {
      return lhs.x_coordinate() == rhs.x_coordinate() &&
          lhs.y_coordinate() == rhs.y_coordinate();
  }

  struct UserCommandToRun;
  inline bool operator==(const Messages::ControlerCommandToRun& lhs, const Messages::ControlerCommandToRun& rhs)
  {
      return lhs.pins_configuration() == rhs.pins_configuration();
  }
}

namespace google::protobuf
{
struct Any;
inline bool operator==(const google::protobuf::Any& lhs, const google::protobuf::Any& rhs)
{
    if(lhs.Is<Messages::ControlerCommandToRun>() and rhs.Is<Messages::ControlerCommandToRun>())
    {
        Messages::ControlerCommandToRun lhsPayload;
        Messages::ControlerCommandToRun rhsPayload;
        lhs.UnpackTo(&lhsPayload);
        rhs.UnpackTo(&rhsPayload);

        return lhsPayload == rhsPayload;
    }

    return false;
}
}

TEST_F(VehicleControlerTest, shouldStartVehicleAfterReceiveStartsCommand)
{
    EXPECT_CALL(_vehicleMock, startVehicle());
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, shouldStopVehicleAfterReceiveStopsCommand)
{
    EXPECT_CALL(_vehicleMock, stopVehicle());
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(3)
            .WillOnce(Return(createSerializedUserCommandToStart()))
            .WillOnce(Return(createSerializedUserCommandToStop()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    _sut.controlVehicle();
}

TEST_F(VehicleControlerTest, afterReceiveUserCommandToRunShouldApplyAndSendNewVehicleConfiguration)
{
    EXPECT_CALL(_communicationSocketMock, takeMessageFromQueue()).Times(2)
            .WillOnce(Return(createSerializedUserCommandToRun()))
            .WillOnce(Return(createSerializedDeactivateMessage()));

    Messages::CoordinateSystem coordinates;
    coordinates.set_x_coordinate(xCoordinate);
    coordinates.set_y_coordinate(yCoordinate);

    PinsConfiguration configuration = {{1, 1}, {2, 0}};
    auto messageToSend = ControlerCommandToRunMessageBuilder{}.pinsConfiguration(configuration)
                                                              .build();

    EXPECT_CALL(_vehicleMock, applyNewConfiguration(coordinates));
    EXPECT_CALL(_vehicleMock, getCurrentPinsConfiguration()).WillOnce(Return(configuration));
    EXPECT_CALL(_communicationSocketMock, sendMessage(messageToSend));

    _sut.controlVehicle();

}
