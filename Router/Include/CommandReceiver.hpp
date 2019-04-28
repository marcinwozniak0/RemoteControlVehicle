#pragma once

#include <string>
#include <memory>
#include <queue>

class CommandReceiver
{
public:
    CommandReceiver() = default;
    virtual ~CommandReceiver() = default;

    virtual void receiveCommand();
    virtual void queueCommand(const std::string& command);
    virtual std::shared_ptr<std::queue<std::string>> shareCommandsQueue();

private:
     std::shared_ptr<std::queue<std::string>> _commandsQueue = std::make_shared<std::queue<std::string>>();
};
