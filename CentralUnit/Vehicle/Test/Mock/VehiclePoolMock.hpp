#pragma once

#include <gmock/gmock.h>

#include "VehiclePool.hpp"

class VehiclePoolMock : public VehiclePool
{
public:
    MOCK_METHOD(bool, rentVehicle, (int), ());
    MOCK_METHOD(bool, registerVehicle, (int), ());
    MOCK_METHOD(std::optional<std::shared_ptr<Vehicle>>, getVehicle, (int), ());
};
