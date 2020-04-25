#pragma once

#include "VehicleTypes.hpp"

class SteeringWheel
{
public:
    virtual bool setPinsConfiguration(const PinsConfiguration&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~SteeringWheel() = default;
};
