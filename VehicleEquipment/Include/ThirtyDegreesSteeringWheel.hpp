#pragma once

#include <utility>

#include "SteeringWheel.hpp"

class ThirtyDegreesSteeringWheel : public SteeringWheel
{
public:
    ThirtyDegreesSteeringWheel(const uint8_t);
    ~ThirtyDegreesSteeringWheel() = default;

    bool setPinsConfiguration(const PinsConfiguration&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    PinsConfiguration _pinConfiguration;
    int8_t _steeringAngle;
};
