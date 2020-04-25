#pragma once

#include <array>

#include <UserCommandToRun.pb.h>

#include "VehicleTypes.hpp"

class EngineDriver
{
public:
    virtual void fillPinsConfiguration(const Commands::CoordinateSystem&, PinsConfiguration&) const = 0;

    virtual ~EngineDriver() = default;
};
