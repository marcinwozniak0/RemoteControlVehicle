#pragma once

#include <gmock/gmock.h>

#include "SteeringSystem.hpp"

class SteeringSystemMock : public SteeringSystem
{
public:
    MOCK_METHOD1(applyNewConfigurationBasedOnCoordinates, void(const std::pair<int32_t, int32_t>&));
};
