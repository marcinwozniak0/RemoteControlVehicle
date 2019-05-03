#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "EngineMock.hpp"
#include "SingleAxisPropulsionSystem.hpp"

using namespace ::testing;

class SingleAxisPropulsionSystemTest : public Test
{
public:
    SingleAxisPropulsionSystemTest()
        : _sut(_rightEngineMock, _leftEngineMock)
    {}

    SingleAxisPropulsionSystem _sut;
    NiceMock<EngineMock> _rightEngineMock;
    NiceMock<EngineMock> _leftEngineMock;
};
