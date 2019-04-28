#pragma once

#include <string>
#include <memory>
#include <queue>

class CommandReceiver
{
public:
    CommandReceiver(std::shared_ptr<std::queue<std::string>> commandsQueue);
    virtual ~CommandReceiver() = default;

    virtual void receiveCommand();
    virtual void queueCommand(const std::string& command);

private:
     std::shared_ptr<std::queue<std::string>> _commandsQueue;
};
