#include <Deactivate.pb.h>
#include <UserCommandToStop.pb.h>
#include <UserCommandToStart.pb.h>
#include <UserCommandToRun.pb.h>
#include <ControlerCommandToRun.pb.h>
#include <RegisterVehicle.pb.h>
#include <RegisterUserCommand.pb.h>
#include <ThreeWheeledVehicleConfiguration.pb.h>
#include <google/protobuf/any.pb.h>

#include "UtCommandsBuilders.hpp"

namespace
{
constexpr auto firstEngineFirstInput = 1u;
constexpr auto firstEngineSecondInput = 0u;
constexpr auto firstEnginePwm = 3u;
constexpr auto secondEngineFirstInput = 4u;
constexpr auto secondEngineSecondInput = 5u;
constexpr auto secondEnginePwm = 6u;
constexpr auto steeringWheelPwm = 7u;
auto pwmRange = 255u;
}//namespace

namespace UTHelpers
{

ThreeWheeledVehicleConfiguration createThreeWheeledVehicleConfiguration()
{
    ThreeWheeledVehicleConfiguration vehicleConfiguration;
    vehicleConfiguration.set_first_engine_first_output(firstEngineFirstInput);
    vehicleConfiguration.set_first_engine_second_output(firstEngineSecondInput);
    vehicleConfiguration.set_first_engine_pwm(firstEnginePwm);
    vehicleConfiguration.set_second_engine_first_output(secondEngineFirstInput);
    vehicleConfiguration.set_second_engine_second_output(secondEngineSecondInput);
    vehicleConfiguration.set_second_engine_pwm(secondEnginePwm);
    vehicleConfiguration.set_steering_wheel_pwm(steeringWheelPwm);
    vehicleConfiguration.set_steering_wheel_pwm_range(pwmRange);
    vehicleConfiguration.set_engines_pwm_range(pwmRange);

    return vehicleConfiguration;
}

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

    Commands::CoordinateSystem coordinateSystem;
    coordinateSystem.set_x_coordinate(xCoordinate);
    coordinateSystem.set_y_coordinate(yCoordinate);

    *userCommandToRun.mutable_coordinate_system() = coordinateSystem;

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
    registerVehicleCommand.set_vehicle_type(VehicleType::THREE_WHEELED);

    ThreeWheeledVehicleConfiguration vehicleConfiguration = createThreeWheeledVehicleConfiguration();
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

