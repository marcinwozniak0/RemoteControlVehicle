#pragma once

#include <gtest/gtest.h>

#include "InternalVehiclePool.hpp"

using namespace ::testing;

class InternalVehiclePoolTest : public Test
{
public:
    InternalVehiclePool _sut;

    void registerVehicle(Commands::RegisterVehicle&&);
    void rentVehicle(const int vehicleId);
};