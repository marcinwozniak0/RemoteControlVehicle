#include "Vehicle.hpp"

Vehicle::Vehicle(const PropulsionSystem& propulsionSystem)
    : _propulsionSystem(propulsionSystem)
{
    _vehicleState = VehicleState::Idle;
}

void Vehicle::startVehicle()
{
    _vehicleState = VehicleState::Manual;
}

void Vehicle::stopVehicle()
{
    _vehicleState = VehicleState::Idle;
}

void Vehicle::switchToAutomaticMode()
{
    _vehicleState = VehicleState::Auto;
}

VehicleState Vehicle::getVehicleState()
{
    return _vehicleState;
}
