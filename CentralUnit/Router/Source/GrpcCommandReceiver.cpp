#include "GrpcCommandReceiver.hpp"
#include "Logger.hpp"

GrpcCommandReceiver::GrpcCommandReceiver(const std::string& portAddress) 
{
    startListeningOnPort(portAddress);
}

std::optional<const google::protobuf::Any> GrpcCommandReceiver::takeMessageFromQueue() 
{
    if (not _commandsQueue.empty())
    {
        const auto message = _commandsQueue.front();
        _commandsQueue.pop();
        return message;
    }
    else
    {
        return {};
    }
}

grpc::Status GrpcCommandReceiver::SendCommand(grpc::ServerContext* context, const google::protobuf::Any* request, Commands::EmptyAcknowledge* response)
{
    INFO("Command received. Command will be queued");
    _commandsQueue.push(*request);
    return grpc::Status::OK;
}

grpc::Status GrpcCommandReceiver::SayHello(grpc::ServerContext* context, const InitCommands::HelloRequest* request, InitCommands::HelloReply* response)
{
    INFO("Received HelloMessage from " + request->name());

    response->set_message("Successfully conected with server");

    return grpc::Status::OK;
}

void GrpcCommandReceiver::startListeningOnPort(const std::string& portAddress)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(portAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    _server = builder.BuildAndStart();
    
    INFO("Server listening on port: " + portAddress);
}
