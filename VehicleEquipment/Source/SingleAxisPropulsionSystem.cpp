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

void SingleAxisPropulsionSystem::transferCharacteristicValues(const std::pair<int32_t, int32_t>& characteristic)
{
    const auto pinValues = _engineDriver.calculatePinValues(characteristic);
    _leftEngine.saveValues(pinValues.at(0));
    _rightEngine.saveValues(pinValues.at(1));
    _rightEngine.startEngine(); //TODO extract to separate method startEngines()
    _leftEngine.startEngine();
}
