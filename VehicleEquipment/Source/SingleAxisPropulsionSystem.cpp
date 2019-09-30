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
    constexpr auto pinConfigurationForFirstEngine = 0u;
    constexpr auto pinConfigurationForSecondEngine = 1u;

    _leftEngine.setConfiguration(pinConfiguration.at(pinConfigurationForFirstEngine));
    _rightEngine.setConfiguration(pinConfiguration.at(pinConfigurationForSecondEngine));
    _rightEngine.activateConfiguration();
    _leftEngine.activateConfiguration();
}
