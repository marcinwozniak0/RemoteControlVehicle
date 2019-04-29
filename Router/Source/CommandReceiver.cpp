#include "CommandReceiver.hpp"

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

std::shared_ptr<CommandsQueue> CommandReceiver::shareCommandsQueue()
{
    return _commandsQueue;
}
