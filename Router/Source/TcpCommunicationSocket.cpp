#include <fstream>

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
    boost::asio::streambuf receiveBuffer;
    boost::system::error_code error;
    boost::asio::read(_socket, receiveBuffer, boost::asio::transfer_all(), error);
    if(error and error not_eq boost::asio::error::eof)
    {
        //TODO throw receivingFailed
    }
    else
    {
        auto receivedData = boost::asio::buffer_cast<const char*>(receiveBuffer.data());
        auto commandsToQueue = getSerialziedMessagesFormBuffer(receivedData);

        for (const auto& command : commandsToQueue)
        {
            _commandsQueue.push(command);
        }
    }
}

void TcpCommunicationSocket::sendMessage(const std::string& messageToSend)
{
    boost::system::error_code error;
    boost::asio::write( _socket, boost::asio::buffer(messageToSend), error);

    if(error)
    {
       //TODO throw sendingFailed
    }
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
    _socket.connect(ip::tcp::endpoint(boost::asio::ip::address::from_string(_ipAddress), _port), errorHandler);

     if (errorHandler)
     {
         return false;
     }

    return true;
}

std::vector<std::string> TcpCommunicationSocket::getSerialziedMessagesFormBuffer(const std::string& receivedData)
{
    std::vector<std::string> commandsToQueue{};

    constexpr auto endOfMessageCharacter = '\0';
    std::string commandToQueue;
    for (const auto character : (_restOfDataFromPreviousReceivedBuffer + receivedData))
    {
        if (endOfMessageCharacter not_eq character)
        {
            commandToQueue += character;
        }
        else
        {
            commandsToQueue.push_back(commandToQueue);
            commandToQueue.clear();
        }
    }

    _restOfDataFromPreviousReceivedBuffer = commandToQueue;

    return commandsToQueue;
}
