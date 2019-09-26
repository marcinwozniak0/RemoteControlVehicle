#pragma once

#include <gmock/gmock.h>

#include "SteeringWheel.hpp"

class SteeringWheelMock : public SteeringWheel
{
public:
    MOCK_METHOD1(setConfiguration, void(const PinsConfiguration&));
    MOCK_CONST_METHOD0(getConfiguration, const PinsConfiguration&());
};
