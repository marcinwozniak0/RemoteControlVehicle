#pragma once

#include <gmock/gmock.h>

#include "VehiclePool.hpp"

class VehiclePoolMock : public VehiclePool
{
public:
    MOCK_METHOD(std::unique_ptr<Vehicle>, create, (), (const));
};
