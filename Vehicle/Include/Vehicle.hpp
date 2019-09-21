#pragma once

#include "VehicleState.hpp"
#include "Commands.hpp"

class PropulsionSystem;
class SteeringSystem;

class Vehicle
{
public:
    Vehicle(PropulsionSystem&, SteeringSystem&);

    void startVehicle();
    void stopVehicle();
    void switchToAutomaticMode();

    void run(const USER_COMMAND_TO_DRIVE&&); //TODO better name

    VehicleState getVehicleState();

private:
    VehicleState _vehicleState;
    PropulsionSystem& _propulsionSystem;
    SteeringSystem& _steeringSystem;

};
