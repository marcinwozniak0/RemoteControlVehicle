#pragma once

#include <gmock/gmock.h>

#include "VehicleFactory.hpp"

class VehicleFactoryMock : public VehicleFactory
{
public:
    MOCK_METHOD(std::unique_ptr<Vehicle>, create, (Commands::RegisterVehicle&&), (const));
};
