#pragma once

#include <array>

#include "PropulsionSystem.hpp"
#include "Engine.hpp"

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(const std::array<Engine, 2> engines);
private:
    const std::array<Engine, 2> _engines;
};
