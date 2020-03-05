#pragma once

#include <utility>

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(SteeringWheel&  steeringWheel);

    void applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    int calculateSteeringAngle(const Commands::CoordinateSystem&) const;
    int calculatePwmValue(const int steeringAngle) const;

    SteeringWheel& _steeringWheel;
};
