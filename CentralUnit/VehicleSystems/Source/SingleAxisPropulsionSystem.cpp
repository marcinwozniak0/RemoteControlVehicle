#include "SingleAxisPropulsionSystem.hpp"
#include "Engine.hpp"
#include "EngineDriver.hpp"

SingleAxisPropulsionSystem::SingleAxisPropulsionSystem(std::unique_ptr<Engine> rightEngine,
                                                       std::unique_ptr<Engine> leftEngine,
                                                       std::unique_ptr<const EngineDriver> engineDriver)
    : _rightEngine(std::move(rightEngine))
    , _leftEngine(std::move(leftEngine))
    , _engineDriver(std::move(engineDriver))
{}

void SingleAxisPropulsionSystem::applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem& coordinates)
{
    auto boothEnginesPinConfiguration = getPinsConfiguration();
    _engineDriver->fillPinsConfiguration(coordinates, boothEnginesPinConfiguration);
    _leftEngine->setPinsConfiguration(boothEnginesPinConfiguration);
    _rightEngine->setPinsConfiguration(boothEnginesPinConfiguration);
}

const PinsConfiguration SingleAxisPropulsionSystem::getPinsConfiguration() const
{
    auto rightEnginePinsConfiguration = _rightEngine->getPinsConfiguration();
    auto leftEnginePinsConfiguration = _leftEngine->getPinsConfiguration();

    auto& boothEnginesPinsConfiguration = rightEnginePinsConfiguration;
    boothEnginesPinsConfiguration.merge(leftEnginePinsConfiguration);

    return boothEnginesPinsConfiguration;
}
