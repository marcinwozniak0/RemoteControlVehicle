#pragma once

#include <gmock/gmock.h>

#include "VehiclePool.hpp"

class VehiclePoolMock : public VehiclePool
{
public:
    MOCK_METHOD(bool, rentVehicle, (int), (override));
    MOCK_METHOD(bool, registerVehicle, (Commands::RegisterVehicle&&), (override));
    MOCK_METHOD(std::optional<std::shared_ptr<Vehicle>>, getVehicle, (int), (override));
    MOCK_METHOD(const std::vector<int>&, getRentedVehicleIds, (), (const, override));
};
