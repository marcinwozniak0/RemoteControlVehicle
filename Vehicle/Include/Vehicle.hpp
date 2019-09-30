#pragma once

#include <UserCommandToRun.pb.h>

#include "VehicleState.hpp"

class PropulsionSystem;
class SteeringSystem;

class Vehicle
{
public:
    Vehicle(PropulsionSystem&, SteeringSystem&);

    void startVehicle();
    void stopVehicle();
    void switchToAutomaticMode();

    void applyNewConfiguration(const Messages::CoordinateSystem&); //TODO better name

    VehicleState getVehicleState();

private:
    VehicleState _vehicleState;
    PropulsionSystem& _propulsionSystem;
    SteeringSystem& _steeringSystem;

};
