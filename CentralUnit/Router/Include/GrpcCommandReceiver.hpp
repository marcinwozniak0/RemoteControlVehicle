#include <queue>
#include <grpc++/grpc++.h>

#include <Client.grpc.pb.h>

#include "CommandReceiver.hpp"

class GrpcCommandReceiver : public CommandReceiver, public Router::Service 
{
public:
    GrpcCommandReceiver(const std::string& portAddress);

    std::optional<const google::protobuf::Any> takeMessageFromQueue() override;

private:
    grpc::Status SendCommand(grpc::ServerContext* context, const google::protobuf::Any* request, Commands::Acknowledge* response) override;
    grpc::Status SayHello(grpc::ServerContext* context, const InitCommands::HelloRequest* request, InitCommands::HelloReply* response) override;
    void startListeningOnPort(const std::string& portAddress);

    std::queue<google::protobuf::Any> _commandsQueue;
    std::unique_ptr<grpc::Server> _server;
};