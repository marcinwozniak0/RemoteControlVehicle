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

void Vehicle::applyNewConfiguration(const Messages::CoordinateSystem& coordinateSystem)
{
    const auto coordinatesToSend = std::make_pair(coordinateSystem.x_coordinate(), coordinateSystem.y_coordinate());

    _propulsionSystem.applyNewConfigurationBasedOnCoordinates(coordinateSystem);
    _steeringSystem.applyNewConfigurationBasedOnCoordinates(coordinatesToSend);
}
