#pragma once

#include <queue>
#include <boost/asio.hpp>

#include "CommunicationSocket.hpp"

using namespace boost::asio;

class TcpCommunicationSocket : public CommunicationSocket
{
public:
    TcpCommunicationSocket(const int port, std::string_view ipAddress);

    void receiveCommand() override;
    void sendCommand(const std::string&) override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    bool connectToSocket();
    void quqeueReceivedCommands(const streambuf&);
    void queueCommandsFormBuffer(const std::string&);
    void saveIncompleteCommandFromBuffer(const std::string&);

    std::queue<std::string> _commandsQueue;

    const int _port;
    const std::string _ipAddress;
    io_service _ioService;
    ip::tcp::socket _socket;
    std::string _restOfDataFromPreviousReceivedBuffer;
};
