#pragma once

#include <gtest/gtest.h>
#include <cstdint>

#include "ThirtyDegreesSteeringWheel.hpp"

namespace
{
constexpr uint8_t steeringWheelPwmPinNumer = 0;
}

using namespace ::testing;

class ThirtyDegreesSteeringWheelTest : public Test
{
public:
    ThirtyDegreesSteeringWheelTest()
        : _sut(steeringWheelPwmPinNumer) {}

    ThirtyDegreesSteeringWheel _sut;
};
