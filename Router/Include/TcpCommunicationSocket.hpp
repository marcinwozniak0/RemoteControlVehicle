#pragma once

#include <queue>
#include <boost/asio.hpp>

#include "CommunicationSocket.hpp"

using namespace boost::asio;

class TcpCommunicationSocket : public CommunicationSocket
{
public:
    TcpCommunicationSocket(const int port, std::string_view ipAddress);

    void receiveMessage() override;
    void sendMessage(const google::protobuf::Any) const override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    void clearAlreadyReadMessagesOnPort() const;
    bool connectToSocket();

    std::queue<std::string> _commandsQueue;

    const int _port;
    const std::string _ipAddress;
    io_service _ioService;
    ip::tcp::socket _socket;
};
