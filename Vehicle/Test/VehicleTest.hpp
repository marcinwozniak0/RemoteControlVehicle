#pragma once

#include <gtest/gtest.h>

#include "Vehicle.hpp"
#include "SingleAxisPropulsionSystem.hpp"
#include "DcEngine.hpp"

class VehicleTest : public ::testing::Test
{
public:
    VehicleTest()
        : _propulsionSystem({_firstEngine, _secondEngine})
        , _sut(_propulsionSystem)
    {}

    DcEngine _firstEngine;
    DcEngine _secondEngine;
    SingleAxisPropulsionSystem _propulsionSystem;
    Vehicle _sut;
};
