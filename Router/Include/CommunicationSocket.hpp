#pragma once

#include <string>
#include <optional>

class CommunicationSocket
{
public:
    virtual void receiveCommand() = 0;
    virtual void sendCommand(const std::string&) = 0;
    virtual std::optional<const std::string> takeMessageFromQueue() = 0;

    virtual ~CommunicationSocket() = default;
};
