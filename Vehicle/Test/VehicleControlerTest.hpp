#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>

#include "VehicleControler.hpp"
#include "CommandReceiverMock.hpp"
#include "EngineMock.hpp"
#include "PropulsionSystemMock.hpp"

namespace
{
const std::shared_ptr<CommandsQueue> COMMANDS_QUEUE = std::make_shared<CommandsQueue>();
}//namespace

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _vehicle(_propulsionSystemMock)
    {
        EXPECT_CALL(_commandReceiverMock, shareCommandsQueue()).WillOnce(Return(COMMANDS_QUEUE));
        _sut = std::make_unique<VehicleControler>(_commandReceiverMock, _vehicle);
    }

    std::unique_ptr<VehicleControler> _sut;
    NiceMock<PropulsionSystemMock> _propulsionSystemMock;
    NiceMock<CommandReceiverMock> _commandReceiverMock;
    Vehicle _vehicle;

private:
    std::shared_ptr<CommandsQueue> _commandQueue;

};

