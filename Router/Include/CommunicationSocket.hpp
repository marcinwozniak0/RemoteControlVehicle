#pragma once

#include <string>
#include <optional>

#include <google/protobuf/any.pb.h>

class CommunicationSocket
{
public:
    virtual void receiveMessage() = 0;
    virtual void sendMessage(const std::string&) = 0;
    virtual std::optional<const std::string> takeMessageFromQueue() = 0;

    virtual ~CommunicationSocket() = default;
};
