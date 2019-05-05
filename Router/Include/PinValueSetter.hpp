#pragma once

#include <stdint.h>

class PinValueSetter
{
public:
    virtual void setValue(uint8_t pin, uint8_t value) const = 0;
};
