#pragma once

#include <UserCommandToRun.pb.h>

#include "Vehicle.hpp"

class PropulsionSystem;
class SteeringSystem;

class ThreeWheeledVehicle : public Vehicle
{
public:
    ThreeWheeledVehicle(PropulsionSystem&, SteeringSystem&);

    void startVehicle() override;
    void stopVehicle() override;
    void switchToAutomaticMode() override;

    void applyNewConfiguration(const Messages::CoordinateSystem&) override;
    PinsConfiguration getCurrentPinsConfiguration() const override;

    VehicleState getVehicleState() override;

private:
    VehicleState _vehicleState;
    PropulsionSystem& _propulsionSystem;
    SteeringSystem& _steeringSystem;

};
