#pragma once

#include <google/protobuf/any.pb.h>

class MessageBuilder
{
public:
    virtual google::protobuf::Any build() const = 0;

    virtual ~MessageBuilder() = default;
};
