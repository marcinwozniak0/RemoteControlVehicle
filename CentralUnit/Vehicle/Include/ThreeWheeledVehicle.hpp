#pragma once

#include <memory>

#include <UserCommandToRun.pb.h>

#include "Vehicle.hpp"

class PropulsionSystem;
class SteeringSystem;

class ThreeWheeledVehicle : public Vehicle
{
public:
    ThreeWheeledVehicle(std::unique_ptr<PropulsionSystem>,
                        std::unique_ptr<SteeringSystem>);

    void startVehicle() override;
    void stopVehicle() override;
    void switchToAutomaticMode() override;

    void applyNewConfiguration(const Commands::CoordinateSystem&) override;
    PinsConfiguration getCurrentPinsConfiguration() const override;

    VehicleState getVehicleState() override;

private:
    VehicleState _vehicleState;
    std::unique_ptr<PropulsionSystem> _propulsionSystem;
    std::unique_ptr<SteeringSystem> _steeringSystem;

};
