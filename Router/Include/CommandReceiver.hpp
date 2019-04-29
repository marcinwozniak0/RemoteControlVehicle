#pragma once

#include <string>
#include <memory>
#include <queue>

namespace
{
using CommandsQueue = std::queue<std::string>;
}//namespace

class CommandReceiver
{
public:
    CommandReceiver() = default;
    virtual ~CommandReceiver() = default;

    virtual void receiveCommand();
    virtual void queueCommand(const std::string& command);
    virtual std::shared_ptr<CommandsQueue> shareCommandsQueue();

private:
     std::shared_ptr<CommandsQueue> _commandsQueue = std::make_shared<CommandsQueue>();
};
