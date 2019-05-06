#include "CommandReceiver.hpp"

void CommandReceiver::queueCommand(const std::string& command)
{
    _commandsQueue->push(command);
}

#include <iostream>
void CommandReceiver::receiveCommand()
{
    //think about mechanism to receiving commands
    //constexpr auto command = "randomCommand";
    std::string command; //tempporary solution
    std::cin >> command;
    queueCommand(command);
}

std::shared_ptr<CommandsQueue> CommandReceiver::shareCommandsQueue()
{
    return _commandsQueue;
}
