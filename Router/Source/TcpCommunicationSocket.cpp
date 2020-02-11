#include <HelloMessages.pb.h>

#include "TcpCommunicationSocket.hpp"
#include "VehicleConfiguration.hpp"
#include "CommunicationSocketException.hpp"

TcpCommunicationSocket::TcpCommunicationSocket(std::shared_ptr<grpc::Channel> channel)
    : _stub(Router::NewStub(channel))
    {
        const auto connectionResult = connectWithServer();
        if ("RPC failed" == connectionResult)
        {
            throw CommunicationSocketException{"RPC failed"};

            //retry czy co robimy ?
        }
    }

std::string TcpCommunicationSocket::connectWithServer() const
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


void TcpCommunicationSocket::receiveCommand()
{
    //zamienic tam w serwerze na any::mesage
}

void TcpCommunicationSocket::quqeueReceivedCommands()
{

}

void TcpCommunicationSocket::sendCommand(const std::string& messageToSend)
{

}

std::optional<const std::string> TcpCommunicationSocket::takeMessageFromQueue()
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
}
