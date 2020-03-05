#pragma once

#include <UserCommandToRun.pb.h>

#include "VehicleTypes.hpp"

class SteeringSystem
{
public:
    virtual void applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~SteeringSystem() = default;
};
