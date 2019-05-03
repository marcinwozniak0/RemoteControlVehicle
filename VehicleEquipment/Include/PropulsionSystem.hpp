#pragma once

#include <vector>
#include <stdint.h>

class PropulsionSystem
{
public:
    virtual void transferCharacteristicValues(const std::vector<uint8_t>&&) = 0;
};
