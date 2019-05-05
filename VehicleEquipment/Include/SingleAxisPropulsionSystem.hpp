#pragma once

#include <array>

#include "PropulsionSystem.hpp"

class Engine;

class SingleAxisPropulsionSystem : public PropulsionSystem
{
public:
    SingleAxisPropulsionSystem(Engine&, Engine&);

     void transferCharacteristicValues(const std::vector<uint8_t>&&) override;

private:
    Engine& _rightEngine;
    Engine& _leftEngine;
    //np class MostekL295D -> calculate Pin value
};
