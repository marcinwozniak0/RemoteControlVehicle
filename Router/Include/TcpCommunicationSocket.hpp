#pragma once

#include <queue>
#include <grpc++/grpc++.h>
#include <memory>

#include <Client.grpc.pb.h>

#include "CommunicationSocket.hpp"

class TcpCommunicationSocket : public CommunicationSocket
{
public:
    TcpCommunicationSocket(std::shared_ptr<grpc::Channel>);

    void receiveCommand() override;
    void sendCommand(const std::string&) override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    std::string connectWithServer() const;
    void quqeueReceivedCommands();

    std::unique_ptr<Router::Stub> _stub;
    std::queue<std::string> _commandsQueue;

};
