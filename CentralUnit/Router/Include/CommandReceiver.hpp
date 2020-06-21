#pragma once

#include <optional>

namespace Commands
{
class Acknowledge;
}

class CommandReceiver
{
public:
    virtual std::optional<const google::protobuf::Any> takeCommandToProcess() = 0;
    virtual void setAcknowledgeToSend(Commands::Acknowledge&&) = 0;

    virtual ~CommandReceiver() = default;
};
