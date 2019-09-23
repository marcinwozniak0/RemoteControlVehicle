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

void Vehicle::run(const Messages::CoordinateSystem& coordinateSystem)
{
    //TODO change int16 to int32 !
    const auto characteristicToSend = std::make_pair(coordinateSystem.x_coordinate(), coordinateSystem.y_coordinate());
    _propulsionSystem.transferCharacteristicValues(characteristicToSend);
    //TODO _steeringSystem.turn();

}
