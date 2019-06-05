#pragma once

#include "SteeringSystem.hpp"

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    void turn(const int16_t turningAngle) override;
};
