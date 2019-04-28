#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>

#include "VehicleControler.hpp"
#include "CommandReceiverMock.hpp"

namespace
{
const std::shared_ptr<std::queue<std::string>> COMMANDS_QUEUE = std::make_shared<std::queue<std::string>>();

}

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
    {
        EXPECT_CALL(_commandReceiverMock, shareCommandsQueue()).WillOnce(Return(COMMANDS_QUEUE));
        _sut = std::make_unique<VehicleControler>(_commandReceiverMock, _vehicle);
    }

    std::unique_ptr<VehicleControler> _sut;
    Vehicle _vehicle;

private:
    StrictMock<CommandReceiverMock> _commandReceiverMock;
    std::shared_ptr<std::queue<std::string>> _commandQueue;
};

