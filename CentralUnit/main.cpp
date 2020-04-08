#include <google/protobuf/stubs/common.h>
#include <grpc++/grpc++.h>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "VehicleConfiguration.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"
#include "GrpcCommandSender.hpp"
#include "GrpcCommandReceiver.hpp"

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    L293DEngineDriver engineDriver;
    DcEngine firstEngine(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_PWM);
    DcEngine secondEngine(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_PWM);
    SingleAxisPropulsionSystem propulsionSystem(firstEngine,
                                                secondEngine,
                                                engineDriver);
    ThirtyDegreesSteeringWheel steeringWheel(PIN_NUMBERS::STEERING_WHEEL_PWM);
    FrontAxialSteeringSystem steeringSystem(steeringWheel);

    ThreeWheeledVehicle vehicle(propulsionSystem, steeringSystem);

    GrpcCommandSender commandSender(std::make_shared<Router::Stub>(
        grpc::CreateChannel("127.0.0.1:3000", grpc::InsecureChannelCredentials())));

    GrpcCommandReceiver commandReceiver("127.0.0.1:5000");

    VehicleControler vehicleControler(commandReceiver,
                                      commandSender,
                                      vehicle);

    try
    {
        vehicleControler.controlVehicle();
    }
    catch(const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        vehicleControler.vehicleEmergencyStop();
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
