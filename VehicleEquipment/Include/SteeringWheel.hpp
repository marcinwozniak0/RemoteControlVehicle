#pragma once

#include <stdint.h>
#include <array>
#include <map>

#include "VehicleConfiguration.hpp"

using PinNumber = uint8_t;
using PinState = uint8_t;
using PinConfiguration = std::map<const PinNumber, PinState>;

class SteeringWheel
{
public:
    virtual void setConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_STEERING_WHEEL>&) = 0;
    virtual const PinConfiguration& getConfiguration() const = 0;
};
