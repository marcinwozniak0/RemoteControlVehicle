#pragma once

#include <gmock/gmock.h>

#include "SteeringSystem.hpp"

class SteeringSystemMock : public SteeringSystem
{
public:
    MOCK_METHOD1(turn, void(const int16_t));
};
