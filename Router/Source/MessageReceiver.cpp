#include "MessageReceiver.hpp"

void MessageReceiver::queueCommand(const std::string& command)
{
    _commandsQueue->push(command);
}

#include <iostream>
void MessageReceiver::receiveMessage()
{
    //think about mechanism to receiving commands
    //constexpr auto command = "randomCommand";
    std::string command; //tempporary solution
    std::cin >> command;
    queueCommand(command);
}

std::shared_ptr<CommandsQueue> MessageReceiver::shareMessagesQueue()
{
    return _commandsQueue;
}
