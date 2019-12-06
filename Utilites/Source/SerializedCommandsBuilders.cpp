#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>

#include "SerializedCommandsBuilders.hpp"

namespace UTHelpers
{
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

const std::string createSerializedUserCommandToRun(const int32_t xCoordinate, const int32_t yCoordinate)
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
}//UTHelpers
