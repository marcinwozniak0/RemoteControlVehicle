#pragma once

#include <gmock/gmock.h>

#include "SteeringSystem.hpp"

class SteeringSystemMock : public SteeringSystem
{
public:
    MOCK_METHOD(void, applyNewConfigurationBasedOnCoordinates, (const Commands::CoordinateSystem&), (override));
    MOCK_METHOD(const PinsConfiguration&, getPinsConfiguration, (), (const, override));
};
