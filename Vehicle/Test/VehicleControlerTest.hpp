#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <chrono>

#include "VehicleControler.hpp"
#include "CommandReceiverMock.hpp"
#include "DcEngine.hpp"
#include "SingleAxisPropulsionSystem.hpp"

namespace
{
const std::shared_ptr<std::queue<std::string>> COMMANDS_QUEUE = std::make_shared<std::queue<std::string>>();

}

using namespace ::testing;

class VehicleControlerTest : public Test
{
public:
    VehicleControlerTest()
        : _propulsionSystem({_firstEngine, _secondEngine})
        , _vehicle(_propulsionSystem)
    {
        EXPECT_CALL(_commandReceiverMock, shareCommandsQueue()).WillOnce(Return(COMMANDS_QUEUE));
        _sut = std::make_unique<VehicleControler>(_commandReceiverMock, _vehicle);
    }

private:
    DcEngine _firstEngine;
    DcEngine _secondEngine;
    SingleAxisPropulsionSystem _propulsionSystem;
    StrictMock<CommandReceiverMock> _commandReceiverMock;
    std::shared_ptr<std::queue<std::string>> _commandQueue;   

public:
    std::unique_ptr<VehicleControler> _sut;
    Vehicle _vehicle;
};

