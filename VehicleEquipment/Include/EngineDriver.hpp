#pragma once

#include <vector>
#include <array>

#include "VehicleConfiguration.hpp"

class EngineDriver
{
public:
    virtual std::array<std::array<uint8_t, NUMBER_OF_PINS_PER_ENGINE>, NUMBER_OF_ENGINES>
    calculatePinValues(const std::vector<uint8_t>&&) const = 0;

    virtual ~EngineDriver() = default;
};