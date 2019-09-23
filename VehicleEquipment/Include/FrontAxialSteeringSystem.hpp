#pragma once

#include <utility>

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(SteeringWheel&  steeringWheel);

    void applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>&) override;
private:
    SteeringWheel& _steeringWheel;
};
