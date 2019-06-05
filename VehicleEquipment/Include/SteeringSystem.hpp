#pragma once

#include <stdint.h>

class SteeringSystem
{
public:
    virtual void turn(const int16_t turningAngle) = 0;
};
