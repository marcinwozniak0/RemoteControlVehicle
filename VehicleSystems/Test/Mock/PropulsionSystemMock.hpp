#pragma once

#include <gmock/gmock.h>

#include "PropulsionSystem.hpp"

class PropulsionSystemMock : public PropulsionSystem
{
public:
    MOCK_METHOD1(applyNewConfigurationBasedOnCoordinates, void(const Messages::CoordinateSystem&));
};
