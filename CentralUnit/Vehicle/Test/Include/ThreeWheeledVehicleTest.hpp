#pragma once

#include <gtest/gtest.h>

#include "ThreeWheeledVehicle.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "MockPointer.hpp"

using namespace ::testing;

class ThreeWheeledVehicleTest : public Test
{
public:
    ThreeWheeledVehicleTest()
        : _propulsionSystemMock(makeMockPointer<NiceMock<PropulsionSystemMock>>())
        , _steeringSystemMock(makeMockPointer<NiceMock<SteeringSystemMock>>())
        , _sut(_propulsionSystemMock.ownershipHandover(),
               _steeringSystemMock.ownershipHandover())
    {}

    MockPointer<NiceMock<PropulsionSystemMock>> _propulsionSystemMock;
    MockPointer<NiceMock<SteeringSystemMock>> _steeringSystemMock;
    ThreeWheeledVehicle _sut;

};
