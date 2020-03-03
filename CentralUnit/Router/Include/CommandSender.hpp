#pragma once

class CommandSender 
{
public:
    virtual void sendCommand(google::protobuf::Any&&) = 0;

    virtual ~CommandSender() = default;
};
