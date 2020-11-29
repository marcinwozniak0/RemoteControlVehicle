#pragma once

#include <gmock/gmock.h>

#include "MessageBuilder.hpp"

class MessageBuilderMock : public MessageBuilder
{
public:
    MOCK_METHOD(google::protobuf::Any, build, (), (const, override));
};
