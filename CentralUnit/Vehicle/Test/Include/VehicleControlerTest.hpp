#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "VehicleControler.hpp"
#include "CommandSenderMock.hpp"
#include "CommandReceiverMock.hpp"
#include "PropulsionSystemMock.hpp"
#include "SteeringSystemMock.hpp"
#include "VehicleMock.hpp"

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _sut(_commandReceiverMock, _commandSenderMock, _vehicleMock)
    {}

    VehicleControler _sut;

    NiceMock<CommandReceiverMock> _commandReceiverMock;
    NiceMock<CommandSenderMock> _commandSenderMock;
    NiceMock<VehicleMock> _vehicleMock;
};

