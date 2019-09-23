#pragma once

#include <gmock/gmock.h>

#include "MessageReceiver.hpp"

class MessageReceiverMock : public MessageReceiver
{
public:
    MOCK_METHOD0(receiveMessage, void());
    MOCK_METHOD1(queueCommand, void(const std::string&));
    MOCK_METHOD0(shareMessagesQueue, std::shared_ptr<CommandsQueue>());
};
