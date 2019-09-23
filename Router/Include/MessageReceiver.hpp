#pragma once

#include <string>
#include <memory>
#include <queue>

namespace
{
using CommandsQueue = std::queue<std::string>;
}//namespace

class MessageReceiver
{
public:
    MessageReceiver() = default;
    virtual ~MessageReceiver() = default;

    virtual void receiveMessage();
    virtual void queueCommand(const std::string& command);
    virtual std::shared_ptr<CommandsQueue> shareMessagesQueue();

private:
     std::shared_ptr<CommandsQueue> _commandsQueue = std::make_shared<CommandsQueue>();
};
