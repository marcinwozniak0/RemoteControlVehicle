#pragma once

#include <gmock/gmock.h>

#include "SteeringSystem.hpp"

class SteeringSystemMock : public SteeringSystem
{
public:
    MOCK_METHOD1(applyNewConfigurationBasedOnCoordinates, void(const Messages::CoordinateSystem&));
    MOCK_CONST_METHOD0(getPinsConfiguration, const PinsConfiguration&());
};
