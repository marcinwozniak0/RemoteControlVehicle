#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <RegisterVehicle.pb.h>
#include <RegisterUserCommand.pb.h>
#include <ThreeWheeledVehicleConfiguration.pb.h>

#include "UtCommandsBuilders.hpp"

namespace UTHelpers
{
google::protobuf::Any createDeactivateCommand()
{
    Commands::Deactivate deactivateMessage;
    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(deactivateMessage);

    return topLevelMessage;
}

google::protobuf::Any createUserCommandToStart(const int vehicleId)
{
    Commands::UserCommandToStart userCommandToStart;
    userCommandToStart.set_vehicle_id(vehicleId);

    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(userCommandToStart);

    return topLevelMessage;
}

google::protobuf::Any createUserCommandToStop(const int vehicleId)
{
    Commands::UserCommandToStop userCommandToStop;
    userCommandToStop.set_vehicle_id(vehicleId);
    google::protobuf::Any topLevelMessage;

    topLevelMessage.PackFrom(userCommandToStop);

    return topLevelMessage;
}

google::protobuf::Any createUserCommandToRun(const int32_t xCoordinate, const int32_t yCoordinate, const int vehicleId)
{
    Commands::UserCommandToRun userCommandToRun;
    google::protobuf::Any topLevelMessage;

    userCommandToRun.set_vehicle_id(vehicleId);
    userCommandToRun.mutable_coordinate_system()->set_x_coordinate(xCoordinate);
    userCommandToRun.mutable_coordinate_system()->set_y_coordinate(yCoordinate);

    topLevelMessage.PackFrom(userCommandToRun);

    return topLevelMessage;
}

google::protobuf::Any createUnknownCommand()
{
    google::protobuf::Any topLevelMessage;
    topLevelMessage.ParseFromString("UnknownCommand");

    return topLevelMessage;
}

google::protobuf::Any createRegisterVehicleCommand(const int vehicleId)
{
    Commands::RegisterVehicle registerVehicleCommand;
    google::protobuf::Any topLevelMessage;

    registerVehicleCommand.set_vehicle_id(vehicleId);
    registerVehicleCommand.set_vehicle_type(Commands::VehicleType::THREE_WHEELED);

    ThreeWheeledVehicleConfiguration vehicleConfiguration {};
    google::protobuf::Any packedVehicleConfiguration {};
    packedVehicleConfiguration.PackFrom(vehicleConfiguration);

    *registerVehicleCommand.mutable_vehicle_configuration() = packedVehicleConfiguration;
    
    topLevelMessage.PackFrom(registerVehicleCommand);

    return topLevelMessage;
}

google::protobuf::Any createRegisterUserCommand(const int vehicleId)
{
    Commands::RegisterUserCommand registerVehicleCommand;
    google::protobuf::Any topLevelMessage;

    registerVehicleCommand.set_vehicle_id(vehicleId);

    topLevelMessage.PackFrom(registerVehicleCommand);

    return topLevelMessage;
}
}//UTHelpers

