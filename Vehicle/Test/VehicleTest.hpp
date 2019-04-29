#pragma once

#include <gtest/gtest.h>

#include "Vehicle.hpp"
#include "PropulsionSystemMock.hpp"
#include "EngineMock.hpp"

using namespace ::testing;

class VehicleTest : public Test
{
public:
    VehicleTest()
        : _sut(_propulsionSystem)
    {}

    NiceMock<PropulsionSystemMock> _propulsionSystem;
    Vehicle _sut;
};
