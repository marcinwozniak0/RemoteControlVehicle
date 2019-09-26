#pragma once

#include <gtest/gtest.h>
#include <cstdint>

#include "ThirtyDegreesSteeringWheel.hpp"

namespace
{
constexpr uint8_t steeringWheelPwmPinNumer = 0;
constexpr uint8_t unknownSteeringWheelPwmPinNumer = 1;
constexpr uint8_t pinValueInNeutralState = 0;
constexpr uint8_t pinValue = 32;
}

using namespace ::testing;

class ThirtyDegreesSteeringWheelTest : public Test
{
public:
    ThirtyDegreesSteeringWheelTest()
        : _sut(steeringWheelPwmPinNumer) {}

    ThirtyDegreesSteeringWheel _sut;
};
