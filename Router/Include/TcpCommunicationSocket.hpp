#pragma once

#include <queue>

#include "CommunicationSocket.hpp"

class TcpCommunicationSocket : public CommunicationSocket
{
public:
    TcpCommunicationSocket(std::string_view portDesignation);

    void receiveMessage() override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    void clearAlreadyReadMessagesOnPort() const;

    std::queue<std::string> _commandsQueue;
    const std::string _portDesignation;
};
