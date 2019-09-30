#pragma once

#include <utility>

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(SteeringWheel&  steeringWheel);

    void applyNewConfigurationBasedOnCoordinates(const std::pair<int32_t, int32_t>&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    int calculateSteeringAngle(const std::pair<int32_t, int32_t>& coordinates) const;
    int calculatePwmValue(const int steeringAngle) const;

    SteeringWheel& _steeringWheel;
};
