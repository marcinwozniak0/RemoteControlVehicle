#pragma once

#include <array>

#include "PropulsionSystem.hpp"

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(Engines engines);

     void transferCharacteristicValues(const std::vector<uint8_t>&&) override;
private:
    Engines _engines;
};
