#pragma once

#include <gmock/gmock.h>

#include "CommandReceiver.hpp"

class CommandReceiverMock : public CommandReceiver
{
public:
    MOCK_METHOD(std::optional<const google::protobuf::Any>, takeCommandToProcess, (), (override));
    MOCK_METHOD(void, setAcknowledgeToSend, (Commands::Acknowledge&&), (override));
};
