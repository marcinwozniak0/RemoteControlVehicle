#include <iostream>

#include "VehicleControler.hpp"

int main()
{
    CommandReceiver commandReceiver;
    Vehicle vehicle;
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
