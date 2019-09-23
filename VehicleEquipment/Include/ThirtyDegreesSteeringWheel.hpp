#pragma once

#include <utility>

#include "SteeringWheel.hpp"

class ThirtyDegreesSteeringWheel : public SteeringWheel
{
public:
    ThirtyDegreesSteeringWheel() = default;
    ~ThirtyDegreesSteeringWheel() = default;
    void setConfiguration(const std::array<uint8_t, NUMBER_OF_PINS_PER_STEERING_WHEEL>&) override;
    const PinConfiguration getConfiguration() override {return {};}

private:
    std::map<PinNumber, PinState> _pinConfiguration;
};
