#pragma once

#include <array>

#include "PropulsionSystem.hpp"

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(const Engines engines);
private:
    const Engines _engines;
};
