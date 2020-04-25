#include "SingleAxisPropulsionSystem.hpp"
#include "Engine.hpp"
#include "EngineDriver.hpp"

SingleAxisPropulsionSystem::SingleAxisPropulsionSystem(Engine& rightEngine,
                                                       Engine& leftEngine,
                                                       const EngineDriver& engineDriver)
    : _rightEngine(rightEngine)
    , _leftEngine(leftEngine)
    , _engineDriver(engineDriver)
{}

void SingleAxisPropulsionSystem::applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem& coordinates)
{
    auto boothEnginesPinConfiguration = getPinsConfiguration();
    _engineDriver.fillPinsConfiguration(coordinates, boothEnginesPinConfiguration);
    _leftEngine.setPinsConfiguration(boothEnginesPinConfiguration);
    _rightEngine.setPinsConfiguration(boothEnginesPinConfiguration);
}

const PinsConfiguration SingleAxisPropulsionSystem::getPinsConfiguration() const
{
    auto rightEnginePinsConfiguration = _rightEngine.getPinsConfiguration();
    auto leftEnginePinsConfiguration = _leftEngine.getPinsConfiguration();

    auto& boothEnginesPinsConfiguration = rightEnginePinsConfiguration;
    boothEnginesPinsConfiguration.merge(leftEnginePinsConfiguration);

    return boothEnginesPinsConfiguration;
}
