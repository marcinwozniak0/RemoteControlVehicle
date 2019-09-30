#pragma once

#include <array>

#include <UserCommandToRun.pb.h>

#include "VehicleConfiguration.hpp"

class EngineDriver
{
public:
    virtual std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
        calculatePinsConfiguration(const Messages::CoordinateSystem&) const = 0;

    virtual ~EngineDriver() = default;
};
