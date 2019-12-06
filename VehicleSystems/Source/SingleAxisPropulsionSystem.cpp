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

void SingleAxisPropulsionSystem::applyNewConfigurationBasedOnCoordinates(const Messages::CoordinateSystem& coordinates)
{
    const auto pinConfiguration = _engineDriver.calculatePinsConfiguration(coordinates);
    if (not pinConfiguration.empty())
    {
        _leftEngine.setPinsConfiguration(pinConfiguration);
        _rightEngine.setPinsConfiguration(pinConfiguration);
    }
}

const PinsConfiguration SingleAxisPropulsionSystem::getPinsConfiguration() const
{
    auto rightEnginePinsConfiguration = _rightEngine.getPinsConfiguration();
    auto leftEnginePinsConfiguration = _leftEngine.getPinsConfiguration();

    auto& boothEnginesPinsConfiguration = rightEnginePinsConfiguration;
    boothEnginesPinsConfiguration.merge(leftEnginePinsConfiguration);

    return boothEnginesPinsConfiguration;
}
