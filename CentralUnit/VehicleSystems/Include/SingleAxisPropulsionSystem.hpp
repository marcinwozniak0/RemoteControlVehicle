#pragma once

#include <memory>

#include "PropulsionSystem.hpp"

class Engine;
class EngineDriver;

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(std::unique_ptr<Engine>,
                               std::unique_ptr<Engine>,
                               std::unique_ptr<const EngineDriver>);

    void applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem&) override;
    const PinsConfiguration getPinsConfiguration() const override;

private:
    std::unique_ptr<Engine> _rightEngine;
    std::unique_ptr<Engine> _leftEngine;
    std::unique_ptr<const EngineDriver> _engineDriver;
};
