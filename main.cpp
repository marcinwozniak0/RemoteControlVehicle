#include <google/protobuf/stubs/common.h>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "ArduinoPinValueSetter.hpp"
#include "VehicleConfiguration.hpp"
#include "L293DEngineDriver.hpp"
#include "ThirtyDegreesSteeringWheel.hpp"
#include "FrontAxialSteeringSystem.hpp"
#include "ThreeWheeledVehicle.hpp"

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ArduinoPinValueSetter arduinoPinValueSetter(ARDUINO_PORT_DESIGNATION);
    L293DEngineDriver engineDriver;
    DcEngine firstEngine(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_PWM,
                         arduinoPinValueSetter);
    DcEngine secondEngine(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_PWM,
                          arduinoPinValueSetter);
    SingleAxisPropulsionSystem propulsionSystem(firstEngine,
                                                secondEngine,
                                                engineDriver);
    ThirtyDegreesSteeringWheel steeringWheel(PIN_NUMBERS::STEERING_WHEEL_PWM);
    FrontAxialSteeringSystem steeringSystem(steeringWheel);

    ThreeWheeledVehicle vehicle(propulsionSystem, steeringSystem);
    MessageReceiver commandReceiver;
    VehicleControler vehicleControler(commandReceiver,
                                      vehicle,
                                      arduinoPinValueSetter);

    try
    {
        vehicleControler.controlVehicle();
    }
    catch(...)
    {
        vehicleControler.vehicleEmergencyStop();
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
