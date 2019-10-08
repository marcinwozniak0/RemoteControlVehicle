#pragma once

#include <gtest/gtest.h>

#include "ThreeWheeledVehicle.hpp"
#include "PropulsionSystemMock.hpp"
#include "EngineMock.hpp"
#include "SteeringSystemMock.hpp"

using namespace ::testing;

class VehicleTest : public Test
{
public:
    VehicleTest()
        : _sut(_propulsionSystemMock, _steeringSystemMock)
    {}

    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<SteeringSystemMock> _steeringSystemMock;
    ThreeWheeledVehicle _sut;
};
