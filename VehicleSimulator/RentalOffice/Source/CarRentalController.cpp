#include "CarRentalController.hpp"
#include "CommandReceiver.hpp"
#include "GrpcCommandSender.hpp"

#include <ThreeWheeledVehicleConfiguration.pb.h>
#include <google/protobuf/any.pb.h>
#include <RegisterVehicle.pb.h>
#include <RegisterUserCommand.pb.h>

namespace
{
constexpr auto firstEngineFirstInput = 1u;
constexpr auto firstEngineSecondInput = 2u;
constexpr auto firstEnginePwm = 3u;
constexpr auto secondEngineFirstInput = 4u;
constexpr auto secondEngineSecondInput = 5u;
constexpr auto secondEnginePwm = 6u;
constexpr auto steeringWheelPwm = 7u;
auto pwmRange = 255u;

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
}//namespace

void CarRentalController::registerNewItem()
{
    _rentalOffice.registerNewItem();
    auto commandToSend = createRegisterVehicleCommand(5); //TODO how to take ID ?
     _commandSender.sendCommand(std::move(commandToSend));

    //_commandSender.sendCommand() TODO send command
}
