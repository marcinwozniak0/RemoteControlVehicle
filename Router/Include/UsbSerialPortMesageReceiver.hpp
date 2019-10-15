#pragma once

#include <queue>

#include "MessageReceiver.hpp"

class UsbSerialPortMesageReceiver : public MessageReceiver
{
public:
    UsbSerialPortMesageReceiver(std::string_view portDesignation);

    void receiveMessage() override;
    std::optional<const std::string> takeMessageFromQueue() override;

private:
    void clearAlreadyReadMessagesOnPort() const;

    std::queue<std::string> _commandsQueue;
    const std::string _portDesignation;
};
