#include <fstream>
#include <filesystem>

#include "UsbSerialPortMesageReceiver.hpp"

UsbSerialPortMesageReceiver::UsbSerialPortMesageReceiver(std::string_view portDesignation)
    : _portDesignation(portDesignation)
{}

void UsbSerialPortMesageReceiver::receiveMessage()
{
    std::string str;
    std::fstream port;
    port.open(_portDesignation);
    while (port >> str)
    {
       _commandsQueue.push(str);
    }

    clearAlreadyReadMessagesOnPort();
}

void UsbSerialPortMesageReceiver::clearAlreadyReadMessagesOnPort() const
{
    constexpr auto newFileSize = 0u;
    std::filesystem::resize_file(_portDesignation, newFileSize);
}

std::optional<const std::string> UsbSerialPortMesageReceiver::takeMessageFromQueue()
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
