#pragma once

#include <gmock/gmock.h>

#include "FrontAxialSteeringSystem.hpp"
#include "SteeringWheelMock.hpp"
#include  "MockPointer.hpp"

using namespace ::testing;

class FrontAxialSteeringSystemTest : public Test
{
public:
    FrontAxialSteeringSystemTest()
        : _steeringWheelMock(makeMockPointer<NiceMock<SteeringWheelMock>>())
        , _sut(_steeringWheelMock.ownershipHandover()) {}

    MockPointer<NiceMock<SteeringWheelMock>> _steeringWheelMock;
    FrontAxialSteeringSystem _sut;
};

