#pragma once

#include <array>
#include <stdint.h>

#include "VehicleConfiguration.hpp"

class Engine
{
public:
    virtual void saveValues(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&) = 0;
    virtual void startEngine() = 0;

    virtual ~Engine() = default;
};
