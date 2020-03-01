#include <HelloMessages.pb.h>
#include <EmptyAcknowledge.pb.h>

#include "GrpcCommunicationSocket.hpp"
#include "VehicleConfiguration.hpp"
#include "CommunicationSocketException.hpp"
#include "Logger.hpp"

GrpcCommunicationSocket::GrpcCommunicationSocket(std::shared_ptr<Router::StubInterface> stub) 
    : _stub(stub)
{
    const auto connectionResult = connectWithServer();
    if ("RPC failed" == connectionResult)
    {
        throw CommunicationSocketException{"RPC failed"};
    }
}

std::string GrpcCommunicationSocket::connectWithServer() const
{
    HelloRequest request;
    request.set_name("CONTROLER");

    HelloReply reply;

    grpc::ClientContext context;

    grpc::Status status = _stub->SayHello(&context, request, &reply);

    if (status.ok())
    {
        return reply.message();
    } 
    else 
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}


void GrpcCommunicationSocket::receiveCommand()
{
    //TODO receive Any::Message, change Client.proto
}

void GrpcCommunicationSocket::quqeueReceivedCommands()
{

}

#include <iostream>


void GrpcCommunicationSocket::sendCommand(google::protobuf::Any&& commandToSend)
{
    Messages::EmptyAcknowledge acknowledge;

    grpc::ClientContext context;

    grpc::Status status = _stub->SendCommand(&context, commandToSend, &acknowledge);

    if (not status.ok())
    {
        ERROR("Command was not send! " + status.error_message());
    }
}

std::optional<const std::string> GrpcCommunicationSocket::takeMessageFromQueue()
{
    // if (not _commandsQueue.empty())
    // {
    //     const auto message = _commandsQueue.front();
    //     _commandsQueue.pop();
    //     return message;
    // }
    // else
    // {
    //     return {};
    // }

    return {};
}
