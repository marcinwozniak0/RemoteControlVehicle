#include <iostream>
#include <stdio.h>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"
#include "ArduinoPinValueSetter.hpp"
#include "VehicleConfiguration.hpp"

int main()
{
    ArduinoPinValueSetter arduinoPinValueSetter(ARDUINO_PORT_DESIGNATION);
    DcEngine firstEngine(PIN_NUMBERS::FIRST_ENGINE_FIRST_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_SECOND_OUTPUT,
                         PIN_NUMBERS::FIRST_ENGINE_PWM,
                         arduinoPinValueSetter);
    DcEngine secondEngine(PIN_NUMBERS::SECOND_ENGINE_FIRST_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_SECOND_OUTPUT,
                          PIN_NUMBERS::SECOND_ENGINE_PWM,
                          arduinoPinValueSetter);
    SingleAxisPropulsionSystem propulsionSystem(firstEngine, secondEngine);
    Vehicle vehicle(propulsionSystem);
    CommandReceiver commandReceiver;
    VehicleControler vehicleControler(commandReceiver, vehicle);

    try
    {
        vehicleControler.controlVehicle();
    }
    catch(...)
    {
        vehicleControler.vehicleEmergencyStop();
    }

    return 0;
}
