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
    //TODO ^^optional or if isEmpty
    _leftEngine.setPinsConfiguration(pinConfiguration);
    _rightEngine.setPinsConfiguration(pinConfiguration);
}
