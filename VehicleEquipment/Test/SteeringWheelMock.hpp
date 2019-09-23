#pragma once

#include <gmock/gmock.h>

#include "SteeringWheel.hpp"

class SteeringWheelMock : public SteeringWheel
{
public:
    MOCK_METHOD1(setConfiguration, void(const std::array<uint8_t, NUMBER_OF_PINS_PER_STEERING_WHEEL>&));
    MOCK_CONST_METHOD0(getConfiguration, const PinConfiguration&());
};
