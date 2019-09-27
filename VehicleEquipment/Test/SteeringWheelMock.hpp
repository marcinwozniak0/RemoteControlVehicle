#pragma once

#include <gmock/gmock.h>

#include "SteeringWheel.hpp"

class SteeringWheelMock : public SteeringWheel
{
public:
    MOCK_METHOD1(setPinsConfiguration, bool(const PinsConfiguration&));
    MOCK_CONST_METHOD0(getPinsConfiguration, const PinsConfiguration&());
};
