#include <iostream>

#include "VehicleControler.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"

int main()
{
    CommandReceiver commandReceiver;
    DcEngine firstEngine;
    DcEngine secondEngine;
    SingleAxisPropulsionSystem propulsionSystem({std::make_unique<DcEngine>(firstEngine),
                                                 std::make_unique<DcEngine>(secondEngine)});
    Vehicle vehicle(propulsionSystem);
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
