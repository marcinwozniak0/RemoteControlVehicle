#pragma once

#include "VehicleState.hpp"
#include "PropulsionSystem.hpp"

class Vehicle
{
public:
    Vehicle(const PropulsionSystem& propulsionSystem);

    void startVehicle();
    void stopVehicle();
    void switchToAutomaticMode();

    void jedzProsto();

    VehicleState getVehicleState();

private:
    VehicleState _vehicleState;
    const PropulsionSystem& _propulsionSystem;
};
