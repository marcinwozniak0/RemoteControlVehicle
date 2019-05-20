#pragma once

#include <vector>
#include <stdint.h>

class PropulsionSystem
{
public:
    virtual void transferCharacteristicValues(const std::pair<int16_t, int16_t>&) = 0;

    virtual ~PropulsionSystem() = default;
};
