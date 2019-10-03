#pragma once

#include <array>
#include <stdint.h>

#include "VehicleTypes.hpp"
#include "VehicleConfiguration.hpp"

class Engine
{
public:
    virtual void setPinsConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~Engine() = default;
};
