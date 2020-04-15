#include <InitCommands.pb.h>
#include <Acknowledge.pb.h>

#include "GrpcCommandSender.hpp"
#include "VehicleConfiguration.hpp"
#include "CommunicationSocketException.hpp"
#include "Logger.hpp"

GrpcCommandSender::GrpcCommandSender(std::shared_ptr<Router::StubInterface> stub)
    : _stub(stub)
{
    const auto connectionResult = connectWithServer();
    if (std::string::npos != connectionResult.find("RPC failed"))
    {
        ERROR(connectionResult);
        throw CommunicationSocketException{connectionResult};
    }
}

std::string GrpcCommandSender::connectWithServer() const
{
    InitCommands::HelloRequest request;
    request.set_name("CONTROLER");

    InitCommands::HelloReply reply;

    grpc::ClientContext context;

    INFO("Send HelloMessage to server");

    grpc::Status status = _stub->SayHello(&context, request, &reply);

    if (status.ok())
    {
        INFO("Connection with server is established. Received init message = " + reply.message());
        return reply.message();
    } 
    else 
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed. " + status.error_message();
    }
}

void GrpcCommandSender::sendCommand(google::protobuf::Any&& commandToSend)
{
    Commands::Acknowledge acknowledge;

    grpc::ClientContext context;

    grpc::Status status = _stub->SendCommand(&context, commandToSend, &acknowledge);

    if (not status.ok())
    {
        ERROR("Command was not send! " + status.error_message());
    }
}
