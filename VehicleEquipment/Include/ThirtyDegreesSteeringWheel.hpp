#pragma once

#include <utility>

#include "SteeringWheel.hpp"

class ThirtyDegreesSteeringWheel : public SteeringWheel
{
public:
    ThirtyDegreesSteeringWheel(const uint8_t);
    ~ThirtyDegreesSteeringWheel() = default;
    void setConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_STEERING_WHEEL>&) override;
    const PinConfiguration& getConfiguration() const override;

private:
    PinConfiguration _pinConfiguration;
};
