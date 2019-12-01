#include "TcpCommunicationSocket.hpp"
#include "VehicleConfiguration.hpp"
#include "CommunicationSocketException.hpp"

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
    streambuf receivedBuffer;
    boost::system::error_code errorCode;
    read(_socket, receivedBuffer, transfer_all(), errorCode);

    if(errorCode and errorCode not_eq error::eof)
    {
        throw CommunicationSocketException{"Receiving command from tcp/ip socket failed"};
    }
    else
    {
        quqeueReceivedCommands(receivedBuffer);
    }
}

void TcpCommunicationSocket::quqeueReceivedCommands(const streambuf& receivedBuffer)
{
    const auto receivedData = buffer_cast<const char*>(receivedBuffer.data());
    queueCommandsFormBuffer(receivedData);
    saveIncompleteCommandFromBuffer(receivedData);
}

void TcpCommunicationSocket::sendMessage(const std::string& messageToSend)
{
    boost::system::error_code error;
    write( _socket, buffer(messageToSend), error);

    if(error)
    {
       throw CommunicationSocketException{"Sending command to tcp/ip socket failed"};
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
    _socket.connect(ip::tcp::endpoint(ip::address::from_string(_ipAddress), _port), errorHandler);

     if (errorHandler)
     {
         return false;
     }

    return true;
}

void TcpCommunicationSocket::queueCommandsFormBuffer(const std::string& receivedData)
{
    std::string commandToQueue;
    for (const auto serializedCommandCharacter : (_restOfDataFromPreviousReceivedBuffer + receivedData))
    {
        if (END_OF_COMMAND_CHARACTER not_eq serializedCommandCharacter)
        {
            commandToQueue += serializedCommandCharacter;
        }
        else
        {
            _commandsQueue.push(commandToQueue);
            commandToQueue.clear();
        }
    }
}

void TcpCommunicationSocket::saveIncompleteCommandFromBuffer(const std::string& receivedData)
{
    const auto possition = receivedData.find_last_of(END_OF_COMMAND_CHARACTER);

    if (std::string::npos not_eq possition)
    {
        _restOfDataFromPreviousReceivedBuffer = receivedData.substr(possition);
    }
    else
    {
        _restOfDataFromPreviousReceivedBuffer = receivedData;
    }
}
