#pragma once

#include <queue>
#include <grpc++/grpc++.h>
#include <memory>

#include <Client.grpc.pb.h>

#include "CommunicationSocket.hpp"

class GrpcCommunicationSocket : public CommunicationSocket
{
public:
    GrpcCommunicationSocket(std::shared_ptr<Router::StubInterface>);

    void receiveCommand() override;
    void sendCommand(google::protobuf::Any&&) override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    std::string connectWithServer() const;
    void quqeueReceivedCommands();

    std::shared_ptr<Router::StubInterface> _stub;
    std::queue<std::string> _commandsQueue;

};
