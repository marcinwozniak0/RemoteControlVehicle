#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>

#include "UtCommandsBuilders.hpp"

namespace UTHelpers
{
const google::protobuf::Any createDeactivateCommand()
{
    Commands::Deactivate deactivateMessage;
    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(deactivateMessage);

    return topLevelMessage;
}

const google::protobuf::Any createUserCommandToStart()
{
    Commands::UserCommandToStart userCommandToStart;
    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(userCommandToStart);

    return topLevelMessage;
}

const google::protobuf::Any createUserCommandToStop()
{
    Commands::UserCommandToStop userCommandToStop;
    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(userCommandToStop);

    return topLevelMessage;
}

const google::protobuf::Any createUserCommandToRun(const int32_t xCoordinate, const int32_t yCoordinate)
{
    Commands::UserCommandToRun userCommandToRun;
    google::protobuf::Any topLevelMessage;

    userCommandToRun.mutable_coordinate_system()->set_x_coordinate(xCoordinate);
    userCommandToRun.mutable_coordinate_system()->set_y_coordinate(yCoordinate);

    topLevelMessage.PackFrom(userCommandToRun);

    return topLevelMessage;
}

const google::protobuf::Any createUnknownCommand()
{
    google::protobuf::Any topLevelMessage;
    topLevelMessage.ParseFromString("UnknownCommand");

    return topLevelMessage;
}

}//UTHelpers
