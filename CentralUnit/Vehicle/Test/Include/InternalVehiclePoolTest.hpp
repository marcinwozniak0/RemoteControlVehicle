#pragma once

#include <gtest/gtest.h>

#include "InternalVehiclePool.hpp"
#include "VehicleFactoryMock.hpp"

using namespace ::testing;

class InternalVehiclePoolTest : public Test
{
public:
    InternalVehiclePoolTest();

    InternalVehiclePool _sut;

    NiceMock<VehicleFactoryMock> _vehicleFactoryMock;

    void registerVehicle(Commands::RegisterVehicle&&);
    void rentVehicle(const int vehicleId);
};
