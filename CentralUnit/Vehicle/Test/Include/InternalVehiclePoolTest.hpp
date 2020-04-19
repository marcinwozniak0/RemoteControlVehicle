#pragma once

#include <gtest/gtest.h>

#include "InternalVehiclePool.hpp"
#include "VehicleFactoryMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "ThreeWheeledVehicle.hpp"

using namespace ::testing;

class InternalVehiclePoolTest : public Test
{
public:
    InternalVehiclePoolTest() 
        : _sut(_vehicleFactoryMock) 
    {
        ON_CALL(_vehicleFactoryMock, create(_)).WillByDefault(Return(ByMove(std::make_unique<ThreeWheeledVehicle>(_propulsionSystemMock, _steeringSystemMock))));
    }

    InternalVehiclePool _sut;

    NiceMock<VehicleFactoryMock> _vehicleFactoryMock;
    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<SteeringSystemMock> _steeringSystemMock;

    void registerVehicle(Commands::RegisterVehicle&&);
    void rentVehicle(const int vehicleId);
};