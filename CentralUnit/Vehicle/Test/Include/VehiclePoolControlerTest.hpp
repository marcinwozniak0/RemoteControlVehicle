#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "VehiclePoolControler.hpp"
#include "CommandSenderMock.hpp"
#include "CommandReceiverMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "VehicleMock.hpp"
#include "VehiclePoolMock.hpp"

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _sut(_commandReceiverMock, _commandSenderMock, _vehiclePoolMock)
    {
        ON_CALL(_vehiclePoolMock, getVehicle(_)).WillByDefault(ReturnRef(_vehicleMock));
    }

    VehiclePoolControler _sut;

    NiceMock<CommandReceiverMock> _commandReceiverMock;
    NiceMock<CommandSenderMock> _commandSenderMock;
    NiceMock<VehiclePoolMock> _vehiclePoolMock;
    NiceMock<VehicleMock> _vehicleMock;
};

