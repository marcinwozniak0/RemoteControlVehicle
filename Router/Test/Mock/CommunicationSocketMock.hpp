#pragma once

#include <gmock/gmock.h>

#include "CommunicationSocket.hpp"

class CommunicationSocketMock : public CommunicationSocket
{
public:
    MOCK_METHOD(void, receiveMessage, ());
    MOCK_METHOD(void, sendMessage, (const std::string&));
    MOCK_METHOD(std::optional<const std::string>, takeMessageFromQueue, ());
};
