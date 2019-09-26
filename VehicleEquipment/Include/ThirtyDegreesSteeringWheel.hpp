#pragma once

#include <utility>

#include "SteeringWheel.hpp"

class ThirtyDegreesSteeringWheel : public SteeringWheel
{
public:
    ThirtyDegreesSteeringWheel(const uint8_t);
    ~ThirtyDegreesSteeringWheel() = default;

    void setConfiguration(const PinsConfiguration&) override;
    const PinsConfiguration& getConfiguration() const override;

private:
    PinsConfiguration _pinConfiguration;
};
