#pragma once

#include "SteeringWheel.hpp"

class ThirtyDegreesSteeringWheel : public SteeringWheel
{

public:
    ThirtyDegreesSteeringWheel();

    uint8_t getMaxTurningAngle() const override {return 1u;}
    void setTurningAngle(const uint8_t) override {}
};

