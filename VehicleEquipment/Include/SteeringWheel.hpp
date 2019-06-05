#pragma once

#include <stdint.h>

class SteeringWheel
{
public:
    virtual uint8_t getMaxTurningAngle() const = 0;
    virtual void setTurningAngle(const uint8_t) = 0;
};
