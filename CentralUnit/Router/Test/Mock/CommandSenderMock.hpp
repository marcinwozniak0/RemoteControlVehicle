#pragma once

#include <gmock/gmock.h>

#include "CommandSender.hpp"

class CommandSenderMock : public CommandSender
{
public:
    MOCK_METHOD(bool, sendCommand, (google::protobuf::Any&&));
};
