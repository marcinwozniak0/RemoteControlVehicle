#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "FrontAxialSteeringSystem.hpp"

using namespace ::testing;

class FrontAxialSteeringSystemTest : public Test
{
public:
    FrontAxialSteeringSystem _sut;
};

