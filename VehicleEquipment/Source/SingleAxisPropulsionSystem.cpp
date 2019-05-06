#include "SingleAxisPropulsionSystem.hpp"
#include "Engine.hpp"

SingleAxisPropulsionSystem::SingleAxisPropulsionSystem(Engine& rightEngine,
                                                       Engine& leftEngine)
    : _rightEngine(rightEngine)
    , _leftEngine(leftEngine)
{}

#include <iostream>
void SingleAxisPropulsionSystem::transferCharacteristicValues(const std::vector<uint8_t>&& characteristic)
{
    std::cout <<"SEGMENT1\n";
    //tmp = L295D.calculatePinValue(characteristic);
    _rightEngine.saveValues({1,1,200});
    //_leftEngine.saveValues(std::move(characteristic));
    _rightEngine.startEngine();
}
