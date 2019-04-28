#pragma once

#include "VehicleState.hpp"

class Vehicle
{
public:
    Vehicle();

    void startVehicle();
    void stopVehicle();
    void switchToAutomaticMode();
    VehicleState getVehicleState();

private:
    VehicleState _vehicleState;
};
