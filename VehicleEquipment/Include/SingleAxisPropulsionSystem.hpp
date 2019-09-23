#pragma once

#include <array>

#include "PropulsionSystem.hpp"

class Engine;
class EngineDriver;

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(Engine&, Engine&, const EngineDriver&);

     void applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>&) override;

private:
    Engine& _rightEngine;
    Engine& _leftEngine;
    const EngineDriver& _engineDriver;
};
