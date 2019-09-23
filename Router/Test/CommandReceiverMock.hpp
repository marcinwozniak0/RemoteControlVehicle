#pragma once

#include <gmock/gmock.h>

#include "CommandReceiver.hpp"

class CommandReceiverMock : public CommandReceiver
{
public:
    MOCK_METHOD0(receiveMessage, void());
    MOCK_METHOD1(queueCommand, void(const std::string&));
    MOCK_METHOD0(shareCommandsQueue, std::shared_ptr<CommandsQueue>());
};
