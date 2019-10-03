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
        : _sut(_propulsionSystem, _steeringSystemMock)
    {}

    NiceMock<PropulsionSystemMock> _propulsionSystem;
    NiceMock<SteeringSystemMock> _steeringSystemMock;
    ThreeWheeledVehicle _sut;
};
