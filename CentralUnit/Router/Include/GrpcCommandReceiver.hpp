#pragma once

#include <queue>
#include <grpc++/grpc++.h>

#include <Client.grpc.pb.h>

#include "CommandReceiver.hpp"

class GrpcCommandReceiver : public CommandReceiver, public Router::Service 
{
public:
    GrpcCommandReceiver(const std::string& portAddress);

    std::optional<const google::protobuf::Any> takeCommandToProcess() override;
    void setAcknowledgeToSend(Commands::Acknowledge&&) override;

private:
    grpc::Status SendCommand(grpc::ServerContext* context, const google::protobuf::Any* request, Commands::Acknowledge* response) override;
    grpc::Status SayHello(grpc::ServerContext* context, const InitCommands::HelloRequest* request, InitCommands::HelloReply* response) override;
    void startListeningOnPort(const std::string& portAddress);
    void waitForCommandProcessingFinish() const;

    std::unique_ptr<grpc::Server> _server;
    std::optional<google::protobuf::Any> _commandToProcess;
    std::optional<Commands::Acknowledge> _acknowledgeToSend;
};
