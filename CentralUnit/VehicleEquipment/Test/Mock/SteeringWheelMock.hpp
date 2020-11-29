#pragma once

#include <gmock/gmock.h>

#include "SteeringWheel.hpp"

class SteeringWheelMock : public SteeringWheel
{
public:
    MOCK_METHOD(bool, setPinsConfiguration, (const PinsConfiguration&), (override));
    MOCK_METHOD(const PinsConfiguration&, getPinsConfiguration, (), (const, override));
};
