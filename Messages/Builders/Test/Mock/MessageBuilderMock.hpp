#pragma once

#include <gmock/gmock.h>

#include "MessageBuilder.hpp"

class MessageBuilderMock : public MessageBuilder
{
public:
    MOCK_CONST_METHOD0(buildMessage, google::protobuf::Any());
};
