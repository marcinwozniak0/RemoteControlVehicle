#pragma once

#include <string>
#include <optional>

class MessageReceiver
{
public:
    virtual void receiveMessage() = 0;
    virtual std::optional<const std::string> takeMessageFromQueue() = 0;

    virtual ~MessageReceiver() = default;
};
