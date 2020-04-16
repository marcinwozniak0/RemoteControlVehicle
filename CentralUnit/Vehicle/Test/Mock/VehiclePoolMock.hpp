#pragma once

#include <gmock/gmock.h>

#include "VehiclePool.hpp"

class VehiclePoolMock : public VehiclePool
{
public:
    MOCK_METHOD(void, addVehicle, (int), ());
    MOCK_METHOD(Vehicle&, getVehicle, (int), ());
    MOCK_METHOD(bool, isVehicleReqistered, (int), (const));
    MOCK_METHOD(bool, isVehicleInUse, (int), (const));
};
