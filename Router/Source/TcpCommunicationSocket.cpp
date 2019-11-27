#include <fstream>
#include <filesystem>

#include "TcpCommunicationSocket.hpp"

TcpCommunicationSocket::TcpCommunicationSocket(const int port, std::string_view ipAddress)
    : _port(port)
    , _ipAddress(ipAddress)
    , _socket(_ioService)
{
    if (not connectToSocket())
    {
        exit(1);
    }
}

void TcpCommunicationSocket::receiveMessage()
{
    //TODO
}

void TcpCommunicationSocket::sendMessage(const google::protobuf::Any messageToSend) const
{
    //TODO
}

std::optional<const std::string> TcpCommunicationSocket::takeMessageFromQueue()
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

bool TcpCommunicationSocket::connectToSocket()
{
    boost::system::error_code errorHandler;
    _socket.connect(ip::tcp::endpoint( boost::asio::ip::address::from_string(_ipAddress), _port), errorHandler);

     if (errorHandler)
     {
         return false;
     }

    return true;
}
