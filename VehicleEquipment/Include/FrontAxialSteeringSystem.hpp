#pragma once

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(const SteeringWheel&  steeringWheel);

    void turn(const int16_t turningAngle) override;
private:
    const SteeringWheel& _steeringWheel;
};
