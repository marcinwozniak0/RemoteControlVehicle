#pragma once

#include <gmock/gmock.h>

#include "Vehicle.hpp"

class VehicleMock : public Vehicle
{
public:
    MOCK_METHOD(void, startVehicle, (), (override));
    MOCK_METHOD(void, stopVehicle, (), (override));
    MOCK_METHOD(void, switchToAutomaticMode, (), (override));
    MOCK_METHOD(void, applyNewConfiguration, (const Commands::CoordinateSystem&), (override));
    MOCK_METHOD(VehicleState, getVehicleState, (), (override));
    MOCK_METHOD(PinsConfiguration, getCurrentPinsConfiguration, (), (const, override));
};
