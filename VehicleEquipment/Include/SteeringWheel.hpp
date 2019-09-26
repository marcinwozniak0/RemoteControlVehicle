#pragma once

#include <stdint.h>
#include <array>
#include <map>

#include "VehicleConfiguration.hpp"

using PinNumber = uint8_t;
using PinState = uint8_t;
using PinsConfiguration = std::map<const PinNumber, PinState>;

class SteeringWheel
{
public:
    virtual void setConfiguration(const PinsConfiguration&) = 0;
    virtual const PinsConfiguration& getConfiguration() const = 0;
};
