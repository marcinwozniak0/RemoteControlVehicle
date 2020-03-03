#pragma once

#include <utility>

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(SteeringWheel&  steeringWheel);

    void applyNewConfigurationBasedOnCoordinates(const Messages::CoordinateSystem&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    int calculateSteeringAngle(const Messages::CoordinateSystem&) const;
    int calculatePwmValue(const int steeringAngle) const;

    SteeringWheel& _steeringWheel;
};
