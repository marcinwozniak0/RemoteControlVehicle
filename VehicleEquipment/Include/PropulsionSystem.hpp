#pragma once

#include <vector>
#include <stdint.h>

class PropulsionSystem
{
public:
    virtual void transferCharacteristicValues(const std::pair<int32_t, int32_t>&) = 0;

    virtual ~PropulsionSystem() = default;
};
