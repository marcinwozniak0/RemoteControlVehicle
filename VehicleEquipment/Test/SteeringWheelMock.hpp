#pragma once

#include <gmock/gmock.h>

#include "SteeringWheel.hpp"

class SteeringWheelMock : public SteeringWheel
{
public:
    MOCK_CONST_METHOD0(getMaxTurningAngle, uint8_t());
    MOCK_METHOD1(setTurningAngle, void(uint8_t));
};

