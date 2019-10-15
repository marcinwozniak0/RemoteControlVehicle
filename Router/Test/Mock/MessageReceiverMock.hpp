#pragma once

#include <gmock/gmock.h>

#include "MessageReceiver.hpp"

class MessageReceiverMock : public MessageReceiver
{
public:
    MOCK_METHOD(void, receiveMessage, ());
    MOCK_METHOD(std::optional<const std::string>, takeMessageFromQueue, ());
};
