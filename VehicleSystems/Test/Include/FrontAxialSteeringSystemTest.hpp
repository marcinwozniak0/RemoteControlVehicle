#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "FrontAxialSteeringSystem.hpp"
#include "SteeringWheelMock.hpp"

using namespace ::testing;

class FrontAxialSteeringSystemTest : public Test
{
public:
    FrontAxialSteeringSystemTest()
        : _sut(_steeringWheelMock) {}

    FrontAxialSteeringSystem _sut;

    NiceMock<SteeringWheelMock> _steeringWheelMock;
};

