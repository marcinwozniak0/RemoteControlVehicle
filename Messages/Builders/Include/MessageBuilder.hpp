#pragma once

#include <google/protobuf/any.h>

class MessageBuilder
{
public:
    virtual google::protobuf::Any buildMessage() const = 0;

    virtual ~MessageBuilder() = default;
};
