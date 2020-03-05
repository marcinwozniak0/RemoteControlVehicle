#pragma once

#include <array>

#include <UserCommandToRun.pb.h>

#include "VehicleTypes.hpp"

class EngineDriver
{
public:
    virtual const PinsConfiguration calculatePinsConfiguration(const Commands::CoordinateSystem&) const = 0;

    virtual ~EngineDriver() = default;
};
