#pragma once

#include <vector>
#include <stdint.h>

class Engine
{
public:
    virtual void saveValues(const std::vector<uint8_t>&&) = 0;
    virtual void startEngine() = 0;

    virtual ~Engine() = default;
};
