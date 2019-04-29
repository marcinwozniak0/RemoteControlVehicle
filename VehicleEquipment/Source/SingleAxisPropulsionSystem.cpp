#include "SingleAxisPropulsionSystem.hpp"

SingleAxisPropulsionSystem::SingleAxisPropulsionSystem(Engines engines)
{
    _engines = std::move(engines);
}

void SingleAxisPropulsionSystem::transferCharacteristicValues(const std::vector<uint8_t>&& characteristic)
{
    for (const auto& engine : _engines)
    {
        engine->setValues(std::move(characteristic));
    }
}
