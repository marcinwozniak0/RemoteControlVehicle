#pragma once

#include <array>
#include <memory>

#include "VehicleConfiguration.hpp"
#include "Engine.hpp"

namespace
{
using Engines = std::array<std::unique_ptr<Engine>, ENGINES_IN_PROPULSION_SYSTEM>;
}//namespace

class PropulsionSystem
{
public:
    virtual void transferCharacteristicValues(const std::vector<uint8_t>&&) = 0;
};
