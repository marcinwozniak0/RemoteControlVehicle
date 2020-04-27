#pragma once

#include <memory>

#include "SteeringSystem.hpp"

class SteeringWheel;

class FrontAxialSteeringSystem : public SteeringSystem
{
public:
    FrontAxialSteeringSystem(std::unique_ptr<SteeringWheel>);

    void applyNewConfigurationBasedOnCoordinates(const Commands::CoordinateSystem&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    int calculateSteeringAngle(const Commands::CoordinateSystem&) const;
    int calculatePwmValue(const int steeringAngle) const;

    std::unique_ptr<SteeringWheel> _steeringWheel;
};
