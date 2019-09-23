#pragma once

#include <array>
#include <stdint.h>

#include "VehicleConfiguration.hpp"

class Engine
{
public:
    virtual void setConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>&) = 0;
    virtual void activateConfiguration() = 0;

    virtual ~Engine() = default;
};
