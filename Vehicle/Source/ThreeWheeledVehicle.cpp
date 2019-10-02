#include "ThreeWheeledVehicle.hpp"
#include "PropulsionSystem.hpp"
#include "SteeringSystem.hpp"

ThreeWheeledVehicle::ThreeWheeledVehicle(PropulsionSystem& propulsionSystem, SteeringSystem& steeringSystem)
    : _propulsionSystem(propulsionSystem)
    , _steeringSystem(steeringSystem)
{
    _vehicleState = VehicleState::Idle;
}

void ThreeWheeledVehicle::startVehicle()
{
    _vehicleState = VehicleState::Manual;
}

void ThreeWheeledVehicle::stopVehicle()
{
    _vehicleState = VehicleState::Idle;
}

void ThreeWheeledVehicle::switchToAutomaticMode()
{
    _vehicleState = VehicleState::Auto;
}

VehicleState ThreeWheeledVehicle::getVehicleState()
{
    return _vehicleState;
}

void ThreeWheeledVehicle::applyNewConfiguration(const Messages::CoordinateSystem& coordinateSystem)
{
    _propulsionSystem.applyNewConfigurationBasedOnCoordinates(coordinateSystem);
    _steeringSystem.applyNewConfigurationBasedOnCoordinates(coordinateSystem);
}
