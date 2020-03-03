#pragma once

#include <optional>

class CommandReceiver
{
public:
    virtual std::optional<const google::protobuf::Any> takeMessageFromQueue() = 0;

    virtual ~CommandReceiver() = default;
};
