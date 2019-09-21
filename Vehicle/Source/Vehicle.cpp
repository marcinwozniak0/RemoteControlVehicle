#include "Vehicle.hpp"
#include "PropulsionSystem.hpp"
#include "SteeringSystem.hpp"

Vehicle::Vehicle(PropulsionSystem& propulsionSystem, SteeringSystem& steeringSystem)
    : _propulsionSystem(propulsionSystem)
    , _steeringSystem(steeringSystem)
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

void Vehicle::run(const USER_COMMAND_TO_DRIVE&& command)
{
    const auto& characteristicToSend = command._coordinateSystem;
    _propulsionSystem.transferCharacteristicValues(characteristicToSend);
}
