#include <google/protobuf/stubs/common.h>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "VehicleConfiguration.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"

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
    TcpCommunicationSocket commandReceiver(PORT, IP_ADDRESS);
    VehicleControler vehicleControler(commandReceiver,
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
