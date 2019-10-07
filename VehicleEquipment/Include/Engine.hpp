#pragma once

#include <array>
#include <stdint.h>

#include "VehicleTypes.hpp"
#include "VehicleConfiguration.hpp"

class Engine
{
public:
    virtual void setPinsConfiguration(const PinsConfiguration&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~Engine() = default;
};
