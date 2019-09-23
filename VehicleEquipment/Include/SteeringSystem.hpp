#pragma once

#include <stdint.h>
#include <utility>

class SteeringSystem
{
public:
    virtual void applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>&) = 0;
};
