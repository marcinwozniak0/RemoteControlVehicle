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

  /* int data[] = {3,6,10,5,13,10,5,13,10};  //Random data we want to send
    FILE *file;
    file = fopen("/dev/ttyACM0","w");  //Opening device file
    int i = 0;
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(file,"%d",data[i]); //Writing to the file
        fprintf(file,"%c",','); //To separate digits
    }
    fclose(file);
    return  0;*/
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
