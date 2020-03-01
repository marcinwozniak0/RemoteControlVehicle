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

grpc::Status GrpcCommandReceiver::SendCommand(grpc::ServerContext* context, const google::protobuf::Any* request, Messages::EmptyAcknowledge* response) 
{
    _commandsQueue.push(*request);
    return grpc::Status::OK;
}

void GrpcCommandReceiver::startListeningOnPort(const std::string& portAddress)
{
    grpc::ServerBuilder builder;

    builder.AddListeningPort(portAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(this);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    INFO("Server listening on port: " + portAddress);

    server->Wait();
}
