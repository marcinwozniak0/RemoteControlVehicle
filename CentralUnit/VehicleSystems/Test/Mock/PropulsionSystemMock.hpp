#pragma once

#include <gmock/gmock.h>

#include "PropulsionSystem.hpp"

class PropulsionSystemMock : public PropulsionSystem
{
public:
    MOCK_METHOD(void, applyNewConfigurationBasedOnCoordinates, (const Commands::CoordinateSystem&), (override));
    MOCK_METHOD(const PinsConfiguration, getPinsConfiguration, (), (const, override));
};
