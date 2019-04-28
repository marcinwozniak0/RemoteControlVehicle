#include <iostream>

#include "VehicleControler.hpp"

int main()
{
    VehicleControler vehicleControler;

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
