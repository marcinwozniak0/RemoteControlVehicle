#pragma once

#include "VehicleTypes.hpp"

class Engine
{
public:
    virtual void setPinsConfiguration(const PinsConfiguration&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~Engine() = default;
};
