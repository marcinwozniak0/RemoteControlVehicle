#pragma once

#include "VehicleTypes.hpp"

class SteeringSystem
{
public:
    virtual void applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~SteeringSystem() = default;
};
