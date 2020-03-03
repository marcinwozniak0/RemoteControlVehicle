#pragma once

#include <UserCommandToRun.pb.h>

#include "VehicleState.hpp"
#include "VehicleTypes.hpp"

class Vehicle
{
public:
    virtual void startVehicle() = 0;
    virtual void stopVehicle() = 0;
    virtual void switchToAutomaticMode() = 0;
    virtual void applyNewConfiguration(const Messages::CoordinateSystem&) = 0;
    virtual PinsConfiguration getCurrentPinsConfiguration() const = 0;
    virtual VehicleState getVehicleState() = 0;

    virtual ~Vehicle() = default;
};
