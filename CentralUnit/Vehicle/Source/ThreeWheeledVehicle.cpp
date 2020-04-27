#include "ThreeWheeledVehicle.hpp"
#include "PropulsionSystem.hpp"
#include "SteeringSystem.hpp"

ThreeWheeledVehicle::ThreeWheeledVehicle(std::unique_ptr<PropulsionSystem> propulsionSystem,
                                         std::unique_ptr<SteeringSystem> steeringSystem)
    : _propulsionSystem(std::move(propulsionSystem))
    , _steeringSystem(std::move(steeringSystem))
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

void ThreeWheeledVehicle::applyNewConfiguration(const Commands::CoordinateSystem& coordinateSystem)
{
    _propulsionSystem->applyNewConfigurationBasedOnCoordinates(coordinateSystem);
    _steeringSystem->applyNewConfigurationBasedOnCoordinates(coordinateSystem);
}

PinsConfiguration ThreeWheeledVehicle::getCurrentPinsConfiguration() const
{
    auto propulsionSystemPinsConfiguration = _propulsionSystem->getPinsConfiguration();
    auto steeringSystemSystemPinsConfiguration = _steeringSystem->getPinsConfiguration();

    auto& vehiclePinsConfiguration = propulsionSystemPinsConfiguration;
    vehiclePinsConfiguration.merge(steeringSystemSystemPinsConfiguration);

    return vehiclePinsConfiguration;
}
