#include "SingleAxisPropulsionSystem.hpp"
#include "Engine.hpp"

SingleAxisPropulsionSystem::SingleAxisPropulsionSystem(Engine& rightEngine,
                                                       Engine& leftEngine)
    : _rightEngine(rightEngine)
    , _leftEngine(leftEngine)
{}

void SingleAxisPropulsionSystem::transferCharacteristicValues(const std::vector<uint8_t>&& characteristic)
{
    //tmp = L295D.calculatePinValue(characteristic);
    _rightEngine.saveValues({1,1,200});
    _leftEngine.saveValues(std::move(characteristic));
}
