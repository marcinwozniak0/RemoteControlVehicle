#pragma once

#include <vector>
#include <stdint.h>

class Engine
{
public:
    virtual void setValues(const std::vector<uint8_t>&&) = 0;
};
