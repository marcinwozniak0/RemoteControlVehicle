#pragma once

#include "VehicleState.hpp"
#include "PropulsionSystem.hpp"
#include "Commands.hpp"

class Vehicle
{
public:
    Vehicle(PropulsionSystem& propulsionSystem);

    void startVehicle();
    void stopVehicle();
    void switchToAutomaticMode();

    void run(const USER_COMMAND_TO_DRIVE&&); //TODO better name

    VehicleState getVehicleState();

private:
    VehicleState _vehicleState;
    PropulsionSystem& _propulsionSystem;
};
