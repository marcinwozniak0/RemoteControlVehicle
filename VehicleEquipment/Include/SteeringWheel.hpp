#pragma once

#include <stdint.h>
#include <array>
#include <map>

#include "VehicleConfiguration.hpp"

using PinNumber = int;
using PinState = int;
using PinsConfiguration = std::map<const PinNumber, PinState>;

class SteeringWheel
{
public:
    virtual bool setPinsConfiguration(const PinsConfiguration&) = 0;
    virtual const PinsConfiguration& getPinsConfiguration() const = 0;

    virtual ~SteeringWheel() = default;
};
