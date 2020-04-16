#pragma once

#include <gtest/gtest.h>

#include "InternalVehiclePool.hpp"

using namespace ::testing;

class InternalVehiclePoolTest : public Test
{
public:
    InternalVehiclePool _sut;

    void registerVehicle(const int vehicleId)
    {
        _sut.registerVehicle(vehicleId);    
    }

    void rentVehicle(const int vehicleId)
    {
         _sut.rentVehicle(vehicleId);    
    }

};