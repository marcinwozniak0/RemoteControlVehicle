#include "CommandReceiver.hpp"

CommandReceiver::CommandReceiver(std::shared_ptr<std::queue<std::string>> commandsQueue)
    : _commandsQueue(commandsQueue)
{}

void CommandReceiver::queueCommand(const std::string& command)
{
    _commandsQueue->push(command);
}

void CommandReceiver::receiveCommand()
{
    //think about mechanism to receiving commands
    constexpr auto command = "randomCommand";
    queueCommand(command);
}
